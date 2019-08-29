# Daniel Gonzalez
# Department of Mathematics
# Florida State University

using Base.Iterators
using DelimitedFiles
using Distributions
using Primes
using Statistics

# Standard Normal cumulative distribution function
φ = x -> cdf(Normal(0, 1), x)

const e = MathConstants.e
const a = [2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637]
const b = [-8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833]
const c = [0.3374754822726147, 0.9761690190917186, 0.1607979714918209, 0.0276438810333863,
           0.0038405729373609, 0.0003951896511919, 0.0000321767881768, 0.0000002888167364, 0.0000003960315187]
const adT = Dict([10=>1.760, 5=>2.323, 2.5=>2.904, 1=>3.690])
const C = 50*(φ(0.145/0.3) - e^(-0.1)*φ(0.055/0.3)) # the Black-Scholes price of the option

# random-shift Halton sequence
function halton(dim, len)
    seq = []
    shift = rand(dim)
    bases = [prime(i) for i = 1:dim]
    for b = 1:dim
        subseq = []
        for i = 1:len
            f = 1
            r = 0
            while i > 0
                f = f/bases[b]
                r = r + f*(i % bases[b])
                i = floor(i/bases[b])
            end
            append!(subseq, (r + shift[b]) % 1)
        end
        append!(seq, subseq)
    end
    return reshape(seq, (len, dim))
end

# Box-Muller algorithm
function bm(u1, u2)
    R = sqrt(-2log(u1))
    θ = 2π*u2
    return (R*cos(θ), R*sin(θ))
end

# Beasley-Springer-Moro algorithm
function bsm(u)
    y = u - 0.5
    if abs(y) < 0.42
        r = y^2
        return y*(((a[4]*r + a[3])*r + a[2])*r + a[1])/((((b[4]*r + b[3])*r + b[2])*r + b[1])*r + 1)
    else
        r = (y > 0) ? (1 - u) : u
        r = log(-log(r))
        x = c[1] + r*(c[2] + r*(c[3] + r*(c[4] + r*(c[5] + r*(c[6] + r*(c[7] + r*(c[8] + r*c[9])))))))
        return (y < 0) ? -x : x
    end
end

# pricing using Box-Muller
function priceBM()
    θ = []
    for k = 1:40
        estimate = 0
        T = 10
        r = 0.1
        σ = 0.3
        K = 50
        Δt = 0.1
        seq = halton(10, 10000)
        list = map(bm, reshape([seq[i, j] for i = 1:10000, j = 1:5], (10000, 5)), reshape([seq[i, j] for i = 1:10000, j = 6:10], (10000, 5)))
        for path = 1:10000
            λ = (S, t) -> (t <= T) ? λ(S*e^((r - σ^2/2)*Δt + σ*sqrt(Δt)*list[path, (t + 1)÷2][((t + 1) % 2) + 1]), t + 1) : S
            S = λ(50, 1)
            C = (S - K > 0) ? S - K : 0
            estimate += C
        end
        append!(θ, estimate*e^(-r)/10000)
    end
    return θ
end

# pricing using Beasley-Springer-Moro
function priceBSM()
    θ = []
    for k = 1:40
        estimate = 0
        T = 10
        r = 0.1
        σ = 0.3
        K = 50
        Δt = 0.1
        list = map(bsm, halton(10, 10000))
        for path = 1:10000
            λ = (S, t) -> (t <= T) ? λ(S*e^((r - σ^2/2)*Δt + σ*sqrt(Δt)*list[path, t]), t + 1) : S
            S = λ(50, 1)
            C = (S - K > 0) ? S - K : 0
            estimate += C
        end
        append!(θ, estimate*e^(-r)/10000)
    end
    return θ
end

# Anderson-Darling test of normality with specified significance level in {10, 5, 2.5, 1}
function ad(θBM, θBSM, significance)
    n = 40
    θBM = (sort(θBM) .- C)./std(θBM)
    θBSM = (sort(θBSM) .- C)./std(θBSM)
    Z = [θBM, θBSM]
    A² = [-n - sum([(2i - 1)*(log(φ(Z[1][i])) + log(1 - φ(Z[1][n + 1 - i]))) for i in eachindex(Z[1])])/n,
          -n - sum([(2i - 1)*(log(φ(Z[2][i])) + log(1 - φ(Z[2][n + 1 - i]))) for i in eachindex(Z[2])])/n]
    resultBM  = (A²[1] > adT[significance]) ? "reject" : "accept"
    resultBSM = (A²[2] > adT[significance]) ? "reject" : "accept"
    return (A², [resultBM resultBSM])
end

θBM = priceBM()
θBSM = priceBSM()
println("Black-Scholes:\t\t", C)
println("Box-Muller:\t\t", mean(θBM), " ", std(θBM))
println("Beasley-Springer-Moro:\t", mean(θBSM), " ", std(θBSM))

A = (ad(θBM, θBSM, 10), ad(θBM, θBSM, 5), ad(θBM, θBSM, 2.5), ad(θBM, θBSM, 1))
println("A²:\t",    A[1][1])
println("10%:\t",   A[1][2])
println("5%:\t",    A[2][2])
println("2.5%:\t",  A[3][2])
println("1%:\t",    A[4][2])

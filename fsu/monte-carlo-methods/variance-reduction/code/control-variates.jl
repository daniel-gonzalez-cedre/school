# Daniel Gonzalez
# Department of Mathematics
# Florida State University

using Base.Iterators
using Distributions
using Primes
using Statistics

const e = MathConstants.e
const a = [2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637]
const b = [-8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833]
const c = [0.3374754822726147, 0.9761690190917186, 0.1607979714918209, 0.0276438810333863,
           0.0038405729373609, 0.0003951896511919, 0.0000321767881768, 0.0000002888167364, 0.0000003960315187]

# Standard Normal cumulative distribution function
φ(x) = cdf(Normal(0, 1), x)

# random-shift Halton sequence in dimension 'dim' of length 'len'
function halton(dim, len)
    seq = []
    shift = rand(dim)
    bases = [prime(p) for p = 1:dim]
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

# price of an arithmetic Asian call option without variance reduction
function crude(r, σ, T, K, S₀, n, N)
    discount = e^(-r*T)
    W = map(bsm, halton(n, N))
    Y = []
    for m = 1:N
        S = S₀ .* [e^((r - σ^2/2)*i/n + σ*W[m, i]) for i = 1:n]
        SA = (S₀ + sum(S))/(n + 1)
        append!(Y, discount*(SA - K > 0 ? SA - K : 0))
    end
    return mean(Y)
end

# price of an arithmetic Asian call option using a geometric Asian call as a control variate
function control(r, σ, T, K, S₀, n, N)
    discount = e^(-r*T)
    s² = σ^2*sum([(2n - (2i - 1))*i/n for i = 1:n])/((n + 1)^2)
    ESG = S₀*e^((r - σ^2/2)*sum([i/n for i = 1:n])/(n + 1) + s²/2)
    d₁ = (log(ESG/K) + s²/2)/sqrt(s²)
    d₂ = (log(ESG/K) - s²/2)/sqrt(s²)
    μ = discount*(ESG*φ(d₁) - K*φ(d₂))
    W = map(bsm, halton(n, N))
    Y = []
    C = []
    for m = 1:N
        S = S₀ .* [e^((r - σ^2/2)*i/n + σ*W[m, i]) for i = 1:n]
        SA = (S₀ + sum(S))/(n + 1)
        SG = (S₀*prod(S))^(1/(n + 1))
        append!(Y, discount*(SA - K > 0 ? SA - K : 0))
        append!(C, discount*(SG - K > 0 ? SG - K : 0))
    end
    μY = mean(Y)
    μC = mean(C)
    β = sum([(Y[i] - μY)*(C[i] - μC) for i = 1:N])/sum([(C[i] - μC)^2 for i = 1:N])
    return mean([Y[i] - β*(C[i] - μC) for i = 1:N])
end

function estimate(num)
    crude1 = [crude(0.035, 0.2, 1, 90, 100, 20, 10000) for i = 1:num]
    crude5 = [crude(0.035, 0.2, 1, 90, 100, 20, 50000) for i = 1:num]
    control1 = [control(0.035, 0.2, 1, 90, 100, 20, 10000) for i = 1:num]
    control5 = [control(0.035, 0.2, 1, 90, 100, 20, 50000) for i = 1:num]

    println("crude:")
    println("\tN = 10000:\t", mean(crude1), "\t", var(crude1))
    println("\tN = 50000:\t", mean(crude5), "\t", var(crude5))
    println("\tN = 100000:\t", crude(0.035, 0.2, 1, 90, 100, 20, 100000))

    println("control:")
    println("\tN = 10000:\t", mean(control1), "\t", var(control1))
    println("\tN = 50000:\t", mean(control5), "\t", var(control5))
    println("\tN = 100000:\t", control(0.035, 0.2, 1, 90, 100, 20, 100000))
end

estimate(50)

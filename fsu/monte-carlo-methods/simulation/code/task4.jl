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

const a = [2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637]
const b = [-8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833]
const c = [0.3374754822726147, 0.9761690190917186, 0.1607979714918209, 0.0276438810333863,
           0.0038405729373609, 0.0003951896511919, 0.0000321767881768, 0.0000002888167364, 0.0000003960315187]
const adT = Dict([15=>1.610, 10=>1.933, 5=>2.492, 2.5=>3.070, 1=>3.857])

# Box-Muller algorithm
function bm()
    u = rand(2)                 # generate two independent pseudorandom numbers in [0, 1)
    R = sqrt(-2log(u[1]))       # R² is exponentially distributed using the inverse transformation method
    θ = 2π*u[2]                 # θ is uniformly distributed in [0, 2π)
    return [R*cos(θ), R*sin(θ)]
end

# Beasley-Springer-Moro algorithm
function bsm()
    u = rand(1)[1]
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

# Anderson-Darling test of normality with specified significance level in {15, 10, 5, 2.5, 1}
function ad(n, sig)
    Z = [sort(collect(flatten([bm() for i = 1:(n ÷ 2)]))),
         sort([bsm() for i = 1:n])]
    A² = [-n - sum((2i - 1)*(log(φ(Z[1][i])) + log(1 - φ(Z[1][n + 1 - i]))) for i in eachindex(Z[1]))/n,
          -n - sum((2i - 1)*(log(φ(Z[2][i])) + log(1 - φ(Z[2][n + 1 - i]))) for i in eachindex(Z[2]))/n]
    resultBM  = (A²[1] > adT[sig]) ? 0 : 1
    resultBSM = (A²[2] > adT[sig]) ? 0 : 1
    return (A², [resultBM resultBSM])
end

# repeat the Anderson-Darling test 100 times at different significance levels
function normality(n)
    Abm = []
    Absm = []
    accepts = zeros(2, 5)
    for i = 1:100
        r = (ad(n, 15), ad(n, 10), ad(n, 5), ad(n, 2.5), ad(n, 1))
        append!(Abm,  (r[1][1][1], r[2][1][1], r[3][1][1], r[4][1][1], r[5][1][1]))
        append!(Absm, (r[1][1][2], r[2][1][2], r[3][1][2], r[4][1][2], r[5][1][2]))
        accepts += reshape([r[1][2] r[2][2] r[3][2] r[4][2] r[5][2]], (2, 5))
    end
    Abm  = reshape(Abm,  (5, 100))
    Absm = reshape(Absm, (5, 100))
    return (Abm, Absm, accepts)
end

data = normality(2000)
open("../data/box-muller.dat", "w") do f
    writedlm(f, data[1])
end
open("../data/beasley-springer-moro.dat", "w") do f
    writedlm(f, data[2])
end
open("../data/table.dat", "w") do f
    writedlm(f, data[3])
end

# Daniel Gonzalez
# Department of Mathematics
# Florida State University

using Statistics

# Standard Normal cumulative distribution function
φ = x -> cdf(Normal(0, 1), x)

const e = MathConstants.e
const a = [2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637]
const b = [-8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833]
const c = [0.3374754822726147, 0.9761690190917186, 0.1607979714918209, 0.0276438810333863,
           0.0038405729373609, 0.0003951896511919, 0.0000321767881768, 0.0000002888167364, 0.0000003960315187]

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
    return μ + η*σ²/k
end

# returns η ~ N(μ, σ²/k)
function sample_mean(k, μ, σ²)
    return μ + bsm()*σ²/k
end

# returns δ² where kδ²/σ² ~ χ² with k degrees of freedom
function sample_var(k, σ²)
    δ² = sum(bsm()^2 for i = 1:(k - 1))
    return δ²*σ²/(k - 1)
end

function MarsagliaSample(k, η, δ²)
    γ = √(k*δ²)
    ϵ = [bsm() for i = 1:k]
    s = sum(ϵ[i]^2 for i in eachindex(ϵ))
    z = [ϵ[i]/√((k - i)*(k - i + 1)*s) for i in eachindex(ϵ)]
    x = [(1 - k)*γ*z[1] + η, γ*sum(z[i] for i = 1:(k - 1)) + η]
    append!(x, γ*sum((j - k)*z[j] for j = 1:(i - 1)) + η for i = 2:(k - 1))
    return x
end

function AntitheticSample(k, x, μ, σ²)
    v = k - 1
    η = 2*μ - sum(x)/k
    δ² = sum((x[i] - μ)^2 for i in eachindex(x))/k
    λ = v*δ²/σ²
    λ = v*(2*(1 - 3/(16*v) - 7/(512*v^2) + 231/(8192*v^3)) - (λ/v)^(1/4))^4
    δ² = λ*σ²/v
    return MarsagliaSample(k, η, δ²)
end

k = 20 
μ = 0
σ² = 1

η = sample_mean(2*k, μ, σ²)
δ² = sample_var(2*k, σ²)
x = MarsagliaSample(2*k, η, δ²)

η = sample_mean(k, μ, σ²)
δ² = sample_var(k, σ²)
y = MarsagliaSample(k, η, δ²)
append!(y, AntitheticSample(k, y, μ, σ²))

println("k: ", k)
println("x: ", x)
println("y: ", y)

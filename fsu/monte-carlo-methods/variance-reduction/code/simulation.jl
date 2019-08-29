# Daniel Gonzalez
# Department of Mathematics
# Florida State University

using Statistics

const e = MathConstants.e
const N = [n*10^4 for n = 1:5]

function crude(n)
    θ = [e^rand() for i = 1:n]
    return (mean(θ), var(θ))
end

function antithetic(n)
    #θ = [(e^u + e^(1 - u))/2 for i = 1:n, u = rand()]
    θ = [(e^u + e^(1 - u))/2 for u in [rand() for i = 1:n]]
    return (mean(θ), var(θ))
end

function control(n)
    C = [rand() for i = 1:n]
    Y = [e^u for u in C]
    μC = mean(C)
    μY = mean(Y)
    β = sum([(y - μY)*(c - μC) for (y, c) in zip(Y, C)])/sum([(c - μC)^2 for c in C])
    θ = [y - β*(c - 0.5) for (y, c) in zip(Y, C)]
    return (mean(θ), var(θ))
end

println("crude:")
for n in N
    println("\tN = ", n, ":\t", crude(n))
end

println("antithetic:")
for n in N
    println("\tN = ", n, ":\t", antithetic(n))
end

println("control:")
for n in N
    println("\tN = ", n, ":\t", control(n))
end

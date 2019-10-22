# Daniel Gonzalez
# Department of Mathematics
# Florida State University

using LinearAlgebra

function ⊗(x, y)
    return [[x[i]*y[j] for j = 1:i] for i = 1:length(x)]
end

# Ax = b
function ×(A, x)
    n = length(A)
    m = length(x)
    shift = n - m + 1
    b = []
    for d = shift:n
        row = []
        for i = shift:d - 1
            append!(row, A[d][i])
        end
        for j = d:n
            append!(row, A[j][d])
        end
        append!(b, sum([row[i]*x[i] for i = 1:m]))
    end
    return b
end

# A = A + α(xyᵀ + (y + αβx)xᵀ)
function householder(A)
    n = length(A)
    for k = 1:n - 2
        x = [A[i][k] for i = k + 1:n]
        γ = (A[k + 1][k] < 0 ? -1 : 1)*norm(x)
        δ = x[1]*γ + γ^2
        x[1] = x[1] + γ
        α = -1/δ
        y = A × x
        β = sum([x[i]*y[i] for i = 1:length(x)])
        z = y .+ α*β.*x
        A = A .+ α*((x ⊗ y) .+ (z ⊗ x))
        A[k + 1][k] = -γ
    end
    T = [[A[i][i] for i = 1:n], [A[i + 1][i] for i = 1:n - 1]]
    return T
end

A = [[4.], [1., 2.], [2., 0., 3], [-5., 4., -1., 1.], [1., 5., 2., 5., -2.], [4., 3., 1., 2., 4., 1.]]

println(householder(A))

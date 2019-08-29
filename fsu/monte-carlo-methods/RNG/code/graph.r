library("plot3D")

# GRAPHING RANDU SEQUENCE
data <- read.csv(file="../output/randu_triples.dat", head=FALSE)
x <- as.numeric(substring(data$V1, 2))
y <- data$V2
z <- as.numeric(substring(data$V3, 1, nchar(as.character(data$V3))-1))
scatter3D(x, y, z, pch=20, theta=73,    phi=7,      bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=74,    phi=4,      bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=75,    phi=1,      bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=77,    phi=-1,     bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=79,    phi=-3,     bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=82,    phi=-5,     bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=84,    phi=-7,     bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=86,    phi=-9,     bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=88,    phi=-11,    bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=90,    phi=-13,    bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=93,    phi=-15,    bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=95,    phi=-17,    bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=97,    phi=-19,    bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=99,    phi=-21,    bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")
scatter3D(x, y, z, pch=20, theta=102,   phi=-23,    bty="g", ticktype="simple", xlab="x", ylab="y", zlab="z")

# GRAPHING MERSENNE TWISTER SEQUENCE
data <- read.csv(file="../output/mersenne_triples.dat", head=FALSE)
x <- as.numeric(substring(data$V1, 2))
y <- data$V2
z <- as.numeric(substring(data$V3, 1, nchar(as.character(data$V3))-1))
scatter3D(x, y, z, pch=20, theta=30, phi=10, bty="g", ticktype="simple",
          xlab="x", ylab="y", zlab="z")

library(tidyverse)

input_raw <- read_lines(here::here("2023/day_10/input.txt")) |>
  stringr::str_split("")

input <- input_raw |>
  unlist() |>
  matrix(nrow = length(input_raw), byrow = T)

valid <- function(x) {
  if (x[1] < 1 || x[1] > nrow(input)) {
    return(FALSE)
  }
  if (x[2] < 1 || x[2] > ncol(input)) {
    return(FALSE)
  }
  TRUE
}

# * Function to find next edges
get_adjacent <- function(i, j) {
  c <- input[i, j]
  up <- c(i - 1, j)
  down <- c(i + 1, j)
  left <- c(i, j - 1)
  right <- c(i, j + 1)
  up_chars <- c("|", "L", "J", "S")
  down_chars <- c("|", "7", "F", "S")
  right_chars <- c("-", "F", "L", "S")
  left_chars <- c("-", "J", "7", "S")
  cands <- list(up, down, left, right)
  exits <- switch(c,
                  "|" = c(TRUE, TRUE, FALSE, FALSE),
                  "-" = c(FALSE, FALSE, TRUE, TRUE),
                  "L" = c(TRUE, FALSE, FALSE, TRUE),
                  "J" = c(TRUE, FALSE, TRUE, FALSE),
                  "7" = c(FALSE, TRUE, TRUE, FALSE),
                  "F" = c(FALSE, TRUE, FALSE, TRUE),
                  "." = c(FALSE, FALSE, FALSE, FALSE),
                  "S" = c(TRUE, TRUE, TRUE, TRUE)
  )
  
  entries <- c(FALSE, FALSE, FALSE, FALSE)
  if (valid(up) && input[up[1], up[2]] %in% down_chars) {
    entries[1] <- TRUE
  }
  if (valid(down) && input[down[1], down[2]] %in% up_chars) {
    entries[2] <- TRUE
  }
  if (valid(left) && input[left[1], left[2]] %in% right_chars) {
    entries[3] <- TRUE
  }
  if (valid(right) && input[right[1], right[2]] %in% left_chars) {
    entries[4] <- TRUE
  }
  cands[exits & entries]
}

start <- which(input == "S", arr.ind = TRUE)
run <- function() {
  sk <- list()
  visited <- list()
  begin <- TRUE
  dists <- matrix(-1, nrow = nrow(input), ncol = ncol(input))

  dists[start[1], start[2]] <- 0
  depths <- list(0)
  sk <- append(list(as.numeric(start)), sk)
  while (length(sk) > 0) {
    # browser()
    v <- sk[[1]]
    sk[[1]] <- NULL
    if (!list(v) %in% visited) {
      visited <- append(visited, list(as.numeric(v)))

      cur_depth <- depths[[1]]
      depths[[1]] <- NULL
      dists[v[1], v[2]] <- cur_depth + 1

      if (v[1] %in% c(0, nrow(input) + 1) || v[2] %in% c(0, ncol(input) + 1)) {
        return(dists)
      }

      for (e in get_adjacent(v[1], v[2])) {
        # browser()
        if (list(e) %in% visited)
          next

        sk <- append(list(as.numeric(e)), sk)
        depths <- append(cur_depth + 1, depths)
        # dists[e[1], e[2]] <- dists[v[1], v[2]] + 1
      }
      last_dist <- dists[v[1], v[2]]
    }
  }
  dists
}

p1 <- run()
ceiling(max(unlist(sapply(get_adjacent(start[1], start[2]), \(x) p1[x[1], x[2]])), na.rm = TRUE) / 2)

# * Part 2
# * Find the polygon
v <- get_adjacent(start[1], start[2])[[which.max(unlist(sapply(get_adjacent(start[1], start[2]), \(x) p1[x[1], x[2]])))]]
path <- list()
val <- 0
while (val != 1) {
  val <- p1[v[1], v[2]]
  cands <- get_adjacent(v[1], v[2])
  path <- append(path, list(v))
  v <- unlist(cands[which(sapply(cands, \(x) p1[x[1], x[2]]) == val - 1)])
  print(val)
}

xy = expand.grid(x = 1:nrow(input), y = 1:ncol(input))
poly = data.frame(x = sapply(path, \(x) x[1]), y = sapply(path, \(x) x[2]))
pip <- secr::pointsInPolygon(
  xy, 
  poly
)
sum(pip)




input <- read.delim(here::here("2023/day_04/input.txt"), sep = ":", header = FALSE) |>
  tidyr::separate_wider_delim(cols = V2, delim = "|", names = c("win_num", "card_num")) |>
  dplyr::mutate(dplyr::across(2:3, \(x) strsplit(trimws(x), "\\s+"))) |>
  dplyr::mutate(win_count = purrr::map2(win_num, card_num, \(x, y) length(intersect(x, y))) |> unlist())

# * Part 1
input |> 
  dplyr::mutate(points = ifelse(win_count > 0, 2^(win_count - 1), 0)) |>
  dplyr::pull(points) |>
  sum()

# * Part 2
win_count <- input$win_count
n <- length(win_count)
copies <- rep(1, n)
for (i in 1:n) {
  if (win_count[i] == 0) next
  ix <- (i + 1):(i + win_count[i])
  ix <- ix[ix <= n]
  copies[ix] <- copies[ix] + copies[i] * 1
}
sum(copies)

# Small GPU Programming Example

## Prerequisite
You will need a machine that has a Nvidia GPU installed. Preferably, it has Nix environment, which is what we use to create the dev environment.

## How-to

1. Enter the dev environment by `nix-shell flake.nix`.
2. Compile the code by `nvcc -o code_exam src/code_exam.cu`
3. Run it. If you want to see the time, you can do `time ./code_exam`

## Disclaimer
You might see the execution time is even longer than running the CPU version, that's because you most likely uncommented the line 62, which copies the result from GPU back to your RAM. And it's a very time-consuming operation.

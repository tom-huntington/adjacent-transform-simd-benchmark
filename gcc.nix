# in file ./shell.nix
{pkgs ? import <nixpkgs> {}} : 
# let 
    # cppcoro = import ./cppcoro.nix {};
    #clang-range-v3 = import ./clang-range-v3.nix { inherit pkgs; };
    # in
#pkgs.llvmPackages_12.libcxxStdenv.mkDerivation {
pkgs.stdenv.mkDerivation {
  name = "clang-nix-shell";
  # nativeBuildInputs = with pkgs; [ cmake ninja];
  buildInputs = with pkgs; [ gbenchmark fmt ]; #cppcoro range-v3 boost175];
  # shellHook = with pkgs; ''
  #     export CPPCORO_INCLUDE=${cppcoro}/include
  #     export CPPCORO_LIBS=${cppcoro}/lib
  #     export RANGE_V3_INCLUDE_DIR=${range-v3}/include
  #   '';
}

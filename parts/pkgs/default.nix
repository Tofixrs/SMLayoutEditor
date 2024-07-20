{inputs, ...}: {
  perSystem = {
    pkgs,
    self',
    ...
  }: let
    configGen = pkgs.callPackage ./configGen.nix {};
    launcher = pkgs.callPackage (import ./launcher.nix self') {};
    mygui = pkgs.callPackage (import ./mygui inputs) {};
  in {
    packages = {
      inherit configGen launcher mygui;
      default = launcher;
    };
  };
}

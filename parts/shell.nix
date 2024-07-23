_: {
  perSystem = {
    pkgs,
    self',
    ...
  }: {
    devShells.default = pkgs.mkShell {
      name = "shell";
      inputsFrom = [self'.packages.configGen];
    };
    devShells.mygui = pkgs.mkShell {
      name = "mygui-shell";
      inputsFrom = [self'.packages.mygui];
    };
  };
}

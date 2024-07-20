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
  };
}

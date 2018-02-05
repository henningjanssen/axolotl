<?php

function t(string $msg): string {
  return \axolotl\translation\Translator::get()->translate($msg);
}

function _t(string $msg, string ...$values): string {
  // UNSAFE nonliteral sprintf
  return sprintf(t($msg), ...$values);
}

<?hh // partial

/**
 * This file/class exists because it allows the test-class
 * that need to modify superglobals to be in a strict-moded file.
 */

namespace axolotl\test;

class Util{
  public static function setGET(array<arraykey, mixed> $val): void{
    $_GET = $val;
  }
  public static function getGET(): array<arraykey, mixed>{
    return $_GET;
  }

  public static function setPOST(array<arraykey, mixed> $val): void{
    $_POST = $val;
  }
  public static function getPOST(): array<arraykey, mixed>{
    return $_POST;
  }

  public static function setSERVER(array<arraykey, mixed> $val): void{
    $_SERVER = $val;
  }
  public static function getSERVER(): array<arraykey, mixed>{
    return $_SERVER;
  }
}

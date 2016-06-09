<?hh // strict

namespace axolotl\util;

class Session{
  public static function loggedIn(): bool{
    return _::SESSION("uid") !== null;
  }

  public static function logout(): void{
    session_destroy();
  }
}

<?hh // strict

namespace axolotl\util;

class Session{
  public static function loggedIn(): bool{
    return _::SESSION("uid") !== null;
  }

  public static function logout(): void{
    if(session_status() !== 2){
      session_start();
    }
    session_destroy();
  }
}

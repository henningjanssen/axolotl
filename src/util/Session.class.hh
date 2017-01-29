<?hh // strict

namespace axolotl\util;

use \axolotl\entities\User;
use \axolotl\exceptions\NotLoggedInException;

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

  public static function getCurrentUser(): User{
    if(!self::loggedIn()){
      throw new NotLoggedInException();
    }
    $entityManager = Doctrine::getEntityManager();
    $user = $entityManager->find(
      "\\axolotl\\entities\\User", _::SESSION("uid")
    );
    return $user;
  }
}

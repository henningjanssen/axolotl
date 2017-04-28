<?hh // strict

namespace axolotl\util;

use \axolotl\entities\User;
use \axolotl\exceptions\NotLoggedInException;

class Session{
  private static ?User $currentUser = null;

  public static function loggedIn(): bool{
    return _::SESSION("uid") !== null;
  }

  public static function logout(): void{
    if(session_status() !== 2){
      session_start();
    }
    session_destroy();
    self::$currentUser = null;
  }

  public static function getCurrentUser(): User{
    if(!self::loggedIn()){
      throw new NotLoggedInException();
    }
    $entityManager = Doctrine::getEntityManager();
    if(self::$currentUser === null){
      self::$currentUser = $entityManager->find(
        "\\axolotl\\entities\\User", _::SESSION("uid")
      );
      $entityManager->persist(self::$currentUser);
    }
    self::$currentUser->setLastActivity();
    $entityManager->flush();
    return self::$currentUser;
  }
}

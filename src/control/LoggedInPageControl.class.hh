<?hh // strict

namespace axolotl\control;

use axolotl\exceptions\NotLoggedInException;
use axolotl\util\Session;

abstract class LoggedInPageControl extends PageControl{
  public function __construct(array<string> $vars){
    if(!Session::loggedIn()){
      throw new NotLoggedInException();
    }
    parent::__construct($vars);
  }
}

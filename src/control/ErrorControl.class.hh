<?hh // strict

namespace axolotl\control;

use \ErrorView;

class ErrorControl extends PageControl{
  public function execute(): void{
    (new ErrorView(intval($this->vars["errno"])))->render();
  }
}

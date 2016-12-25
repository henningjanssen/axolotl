<?hh

namespace axolotl\control;

use \InstallModuleView;

class InstallModuleControl extends LoggedInPageControl{
  public function execute(): void{
    $installAttempt = true;
    (new InstallModuleView($installAttempt, null))->render();
  }
}

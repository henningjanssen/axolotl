<?hh

namespace axolotl\control;

use \InstallModuleView;
use \axolotl\exceptions\BrokenModuleException;
use \axolotl\module\ModuleControl;
use \axolotl\util\_;
use \axolotl\util\Doctrine;
use \axolotl\util\Session;
use \axolotl\util\UploadedZipFile;

class InstallModuleControl extends LoggedInPageControl{
  public function execute(): void{
    $installAttempt = false;
    $newModule = null;
    $error = "";
    if(strlen(strval(_::POST("__ax_modFile")))){ //strval(null) is an empty string
      // we have a file-upload
      try{
        $newModule = $this->installModule();
      }
      catch(BrokenModuleException $ex){
        $error = $ex->getMessage();
      }
      finally{
        $file = new UploadedFile("__ax_modFile");
        $file->delete();
      }
    }
    (new InstallModuleView($installAttempt, $newModule, $error))->render();
  }

  public function installModule(): Module{
    $zip = new UploadedZipFile("__ax_modFile");
    $installAttempt = true;
    // file-existence is checked in getMimeType
    if($zip->getMimeType() !== "application/zip"){
      throw new BrokenModuleException("Not a zip-File");
    }

    $contents = $zip->listContents();

    // ensure the zip contains a a/b/* structure
    $lvlOne = false;
    $lvlTwo = false;
    $modPath = "";

    foreach($contents as $cont){
      //the entry is a directory
      if(substr($cont, -1, 1) === "/"){
        $slashC = substr_count($cont, "/");
        if($slashC == 1){
          if($lvlOne){
            throw new BrokenModuleException("Too many folders in lvl 0");
          }
          $lvlOne = true;
        }
        if($slashC == 2){
          if($lvlTwo){
            throw new BrokenModuleException("Too many folders in lvl 1");
          }
          $lvlTwo = true;
          $modPath = $cont;
        }
      }
    }

    // Check for required files
    $required = array(
      "modinfo.json",
      "install.php"
    );
    foreach($required as $req){
      $reqFile = $modPath.$req;
      if(!in_array($req, $contents)){
        throw new BrokenModuleException("Missing file `$reqFile`");
      }
    }

    $modulesPath = realpath(__DIR__."/../../modules");
    $zip->extractTo($modulesPath);
    $modinfo = json_decode("$modulesPath/{$modPath}modinfo.json");
    $module = Module::newInstance(
      $modinfo['vendor']['name'],
      $modinfo['module']['name'],
      $modinfo['module']['description'],
      $modPath,
      new DateTime(),
      Session::getCurrentUser()
    );
    require_once("$modulesPath/{$modPath}install.php");
    $classname = $modinfo['install']['class'];
    if(!class_exists($classname)){
      throw new BrokenModuleException("Install-class does not exist");
    }

    $install = new $classname();
    if(!($install instanceof ModuleControl)){
      throw new BrokenModuleException(
        "Install-class `$classname` does implement ModuleControl"
      );
    }
    $result = $install->install();
    if($result !== null){
      throw new BrokenModuleException("Installation failed: $result");
    }

    $entityManager = Doctrine::getEntityManager();
    $entityManager->persist($module);
    $entityManager->flush();

    return $module;
  }
}

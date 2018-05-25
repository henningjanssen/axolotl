<?php

namespace axolotl\control;

use \axolotl\view\InstallModuleView;
use \axolotl\entities\Module;
use \axolotl\exceptions\BrokenModuleException;
use \axolotl\module\ModuleControl;
use \axolotl\util\_;
use \axolotl\util\Doctrine;
use \axolotl\util\PathUtil;
use \axolotl\util\Session;
use \axolotl\util\UploadedFile;
use \axolotl\util\UploadedZipFile;

class InstallModuleControl extends LoggedInPageControl{
  private $modRequiredFiles = array(
    "modinfo.json"
  );

  public function execute(): void{
    $newModules = array();
    $errors = array();
    if(strlen(strval(_::POST("__ax_modFile")))){ //strval(null) is an empty string
      // we have a file-upload
      list($newModules, $errors) = $this->installModules();
      $file = new UploadedFile("__ax_modFile");
      $file->delete();
    }
    (new InstallModuleView($newModules, $errors))->render();
  }

  private function installModules(): array {
    $zip = new UploadedZipFile("__ax_modFile");
    $installAttempt = true;
    // file-existence is checked in getMimeType
    if($zip->getMimeType() !== "application/zip"){
      throw new BrokenModuleException("Not a zip-File");
    }

    $modulesPath = PathUtil::MODULE_PATH;
    $modinfo = $this->getContentMetadata($zip, $modulesPath);

    $zip->extractTo($modulesPath);
    $errors = array();
    $entityManager = Doctrine::getEntityManager();
    $newMods = array();
    foreach($modinfo as $info){
      try{
        list($module, $info) = $this->installMod($info);
        $newMods[] = $module;
        if($module->getID() < 0){
          $entityManager->persist($module);
        }
      }
      catch(BrokenModuleException $bmex){
        // There were errors installing the module
        $errors[] = $info['modinfo']['vendor']['name']
          ."/{$info['modinfo']['module']['name']}: {$bmex->getMessage()}";

        // Delete the module-files
        PathUtil::deleteDirectory("$modulesPath{$info['path']}");
      }
    }
    $entityManager->flush();

    return array($newMods, $errors);
  }

  private function getContentMetadata(
    UploadedZipFile $zip, string $modroot
  ): array{
    $contents = $zip->listContents();
    $metadata = array();
    foreach($contents as $cont){
      //the entry is a directory
      // and the root-path of a module
      if(substr($cont, -1, 1) === "/"
        && substr_count($cont, "/") == 2
      ){
        if(!key_exists($cont, $metadata)){
          // check for required files
          $reqFilesExist = true;
          foreach($this->modRequiredFiles as $req){
            if(!in_array("$cont$req", $contents)){
              $reqFilesExist = false;
              break;
            }
          }

          $modinfo = json_decode(
            $zip->getFileFromName("{$cont}modinfo.json"), true
          );
          if(!in_array(
            "{$cont}{$modinfo['install']['file']}", $contents
          )){
            $reqFilesExist = false;
          }

          // add metadata
          $metadata[$cont] = array(
            'path' => $cont,
            'full_path' => "$modroot/$cont",
            'required_exist' => $reqFilesExist,
            'dependencies_exist' => true,
            'modinfo' => $modinfo
          );
        }
      }
    }
    return $metadata;
  }

  private function installMod(array $modinfo): array{
    $module = null;
    $isUpdate = false;

    // check if the module exists and this is an update
    try{
      $module = Module::getByName(
        $modinfo['modinfo']['vendor']['name'],
        $modinfo['modinfo']['module']['name']
      );
      $module->setDescription($modinfo['modinfo']['module']['description']);
      $isUpdate = true;
    }
    catch(axolotl\exceptions\EntityNotFoundException $ex){
      $module = Module::newInstance(
        $modinfo['modinfo']['vendor']['name'],
        $modinfo['modinfo']['module']['name'],
        $modinfo['modinfo']['module']['description'],
        $modinfo['path'],
        new \DateTime(),
        Session::getCurrentUser()
      );
    }

    require_once(
      realpath(
        "{$modinfo['full_path']}"
        ."{$modinfo['modinfo']['install']['file']}"
      )
    );
    $classname = $modinfo['modinfo']['install']['class'];
    if(!class_exists($classname)){
      throw new BrokenModuleException("Install-class does not exist");
    }

    $install = new $classname();
    if(!($install instanceof ModuleControl)){
      throw new BrokenModuleException(
        "Install-class `$classname` does not extend ModuleControl"
      );
    }
    $succ = $isUpdate ? $install->update() : $install->install();
    if(!$succ){
      throw new BrokenModuleException("Installation or update failed");
    }
    $module->setRoutingInfoArray($install->getRoutings());

    return array($module, $modinfo);
  }
}

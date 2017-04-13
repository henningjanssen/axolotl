<?hh // strict

use axolotl\entities\Module;
use axolotl\util\_;

class ModuleView extends PageView{
  public function __construct(
    array<Module> $modules
  ){
    parent::__construct("Modules");
    $baseuri = strval(_::SETTINGS("system.base_uri"));
    $moduleList = <bootstrap:list-group>
      </bootstrap:list-group>;
    foreach($modules as $m){
      $url = "$baseuri/mdetails/".urlencode($m->getVendor())
        .'/'.urlencode($m->getName()).'/';
      $moduleList->appendChild(
        <bootstrap:list-group-item href={$url}>
          <h4>{$m->getName()}</h4>
          <p>{$m->getDescription()}</p>
        </bootstrap:list-group-item>
      );
    }
    if(count($modules) === 0){
      $moduleList->appendChild(
        <bootstrap:list-group-item>
          No modules installed
        </bootstrap:list-group-item>
      );
    }
    $this->content->appendChild(<bootstrap:panel use="info">
        <bootstrap:panel:heading>
          Installed modules
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <bootstrap:button use="info"
            href={"$baseuri/settings/modules/install"}
          >Install new module</bootstrap:button>
          {$moduleList}
        </bootstrap:panel:body>
      </bootstrap:panel>);
  }
}

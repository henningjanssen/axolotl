<?hh // strict

use axolotl\entities\Module;
use axolotl\entities\User;

class HomePageView extends PageView{
  public function __construct(
    User $user, array<Module> $modules
  ){
    parent::__construct(t("Home"));
    $this->content->appendChild(<axolotl:xhp:userinfo user={$user}/>);
    $moduleList = <bootstrap:list-group>
      </bootstrap:list-group>;
    foreach($modules as $m){
      $url = '/m/'.urlencode(strtolower($m->getVendor()))
        .'/'.urlencode(strtolower($m->getName())).'/';
      $moduleList->appendChild(
        <bootstrap:list-group-item href={$url}>
          {$m->getName()}
        </bootstrap:list-group-item>
      );
    }
    if(count($modules) === 0){
      $moduleList->appendChild(
        <bootstrap:list-group-item>
          {t('No modules installed')}
        </bootstrap:list-group-item>
      );
    }
    $this->content->appendChild(<bootstrap:panel use="info">
        <bootstrap:panel:heading>
          {t('Installed modules')}
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          {$moduleList}
        </bootstrap:panel:body>
      </bootstrap:panel>);
  }
}

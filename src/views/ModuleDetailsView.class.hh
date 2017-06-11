<?hh // strict

use axolotl\entities\Module;
use axolotl\util\_;

class ModuleDetailsView extends PageView{
  public function __construct(?Module $module){
    parent::__construct("Modules");
		if($module === null){
			$this->content->appendChild(<bootstrap:alert use="danger">
					This module does not exist or there were problems with the database
				</bootstrap:alert>
			);
			return;
		}
    $this->content->appendChild(
      <bootstrap:panel use="info">
        <bootstrap:panel:heading>
          Module-Information
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <bootstrap:list-group>
            <bootstrap:list-group-item>
              Name: {$module->getName()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Vendor: {$module->getVendor()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Description: {$module->getDescription()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Path: {$module->getPath()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Installation:
							{$module->getInstallationDate()->format('d:m:Y H:i')}
            </bootstrap:list-group-item>
          </bootstrap:list-group>
        </bootstrap:panel:body>
      </bootstrap:panel>
    );

		// Installer
    $this->content->appendChild(
			<axolotl:xhp:userinfo user={$module->getCreator()}/>
    );

		// Show routings
		$routings = <bootstrap:list-group>
		</bootstrap:list-group>;
		foreach($module->getRoutingInfo() as $ri){
			$routings->appendChild(
				<bootstrap:list-group-item>
					{$ri->getPath()} {$ri->getMethodString()}: {$ri->getHandler()}
				</bootstrap:list-group-item>
			);
		}
		$this->content->appendChild(
			<bootstrap:panel use="info">
				<bootstrap:panel:heading>
					Routings
				</bootstrap:panel:heading>
				<bootstrap:panel:body>
					{$routings}
				</bootstrap:panel:body>
			</bootstrap:panel>
		);
  }
}

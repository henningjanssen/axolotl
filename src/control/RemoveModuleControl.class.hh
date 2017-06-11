<?hh

namespace axolotl\control;

use \RedirectView;
use axolotl\entities\Module;
use axolotl\exceptions\EntityNotFoundException;
use axolotl\util\Doctrine;
use axolotl\util\Log;
use axolotl\util\PathUtil;
use axolotl\util\Session;

class RemoveModuleControl extends LoggedInPageControl{
  public function execute(): void{
		$modulesPath = PathUtil::MODULE_PATH;
		$module = Module::getByName($this->vars['vendor'], $this->vars['module']);
		$modInfoF = realpath("$modulesPath{$module->getPath()}/modinfo.json");
		if(file_exists($modInfoF)){
			$modInfo = json_decode(file_get_contents($modInfoF), true);
			require_once(
				"$modulesPath{$module->getPath()}/{$modInfo['install']['file']}"
			);
			$modC = new ($modInfo['install']['class'])();
			$modC->uninstall();
		}
		$entityManager = Doctrine::getEntityManager();
		$entityManager->remove($module);
		$entityManager->flush();
		PathUtil::deleteDirectory("$modulesPath{$module->getPath()}");
		(new RedirectView("/settings/modules"))->render();
  }
}

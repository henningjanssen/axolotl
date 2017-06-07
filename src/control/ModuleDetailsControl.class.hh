<?hh // strict

namespace axolotl\control;

use \ModuleDetailsView;
use axolotl\util\Doctrine;
use axolotl\util\Log;
use axolotl\util\Session;
use axolotl\entities\Module;

class ModuleDetailsControl extends LoggedInPageControl{
  public function execute(): void{
    $qb = Doctrine::getEntityManager()->createQueryBuilder();
		$query = $qb->select('m')
			->from(Module::class, 'm')
			->where(
				$qb->expr()->andX(
					$qb->expr()->eq('m.vendor', ':vendor'),
					$qb->expr()->eq('m.name', ':name')
				)
			)
			->setParameter('vendor', $this->vars['vendor'])
			->setParameter('name', $this->vars['module'])
			->getQuery();
		$module = null;
		try{
			$module = $query->getSingleResult();
		}
		catch(\Doctrine\ORM\NoResultException $nrex){
			Log::error('ModuleDetailsView',
				"Module not found. Query: `{$query->getSQL()}`"
				.", vendor: `{$this->vars['vendor']}`"
				.", module: `{$this->vars['module']}`"
			);
		}
		(new ModuleDetailsView($module))->render();
  }
}

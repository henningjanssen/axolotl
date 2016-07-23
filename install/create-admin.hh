<?hh // partial

require_once '../vendor/autoload.php';

$entityManager = \axolotl\util\Doctrine::getEntityManager();
$user = new \axolotl\entities\User();
$user->setUsername("admin");
$user->setPassword(hash("sha256", "admin"));

$entityManager->persist($user);
$entityManager->flush();

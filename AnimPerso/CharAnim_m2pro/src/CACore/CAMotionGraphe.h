 
class CAMotionGraph
{
	private:
	   //! L'ensemble des BVH du graphe d'animation
	   std::vector<BVH> m_BVH;

	   //! Tous les noeuds du graphe d'animation
	   //! Un noeud du graphe contient l'identifiant de l'animation, le numéro 
	   //! de la frame et les identifiants des noeuds successeurs 
	   std::vector<GrapheNode> m_GrapheNode;

	public:
	   void remplissageGraphe();
	   
};

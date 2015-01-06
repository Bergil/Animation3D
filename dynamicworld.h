#ifndef _DYNAMICWORLD_H_
#define _DYNAMICWORLD_H_


class DynamicWorld
{
	protected:
		std::vector<Particle> m_p;
		std::vector<Spring> m_s;

	public:
		DynamicWorld();
		void init(const int dimX, const int dimY);
		void computeOneStep(const float dt);     // à appeler depus la fonction animate de la class Viewer
		void draw() const;                       // à appeler depuis la fonction draw de la class Viewer
};

#endif
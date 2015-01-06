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
		void computeOneStep(const float dt);
		void draw() const;
};

#endif
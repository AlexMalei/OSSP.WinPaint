#pragma once
#include "Observers/CreationObserver.h"
#include "System/Singleton.h"
#include <vector>
#include "Shapes/Shape.h"

namespace paint
{
	class SceneManager : public Singleton<SceneManager>, public CreationObserver
	{
	public:
		SceneManager();
		~SceneManager();

		void NotifyCreationFinished() override;
		void NotifyCreationStateChanged() override;

		const std::vector<Shape*>& GetShapes() const { return m_shapes; }

	private:
		std::vector<Shape*> m_shapes;
	};
}
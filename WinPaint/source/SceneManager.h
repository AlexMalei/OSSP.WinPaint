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

		void SetButtonsId(DWORD undoButtonId, DWORD redoButtonId);

		void NotifyCreationFinished() override;
		void NotifyCreationStateChanged() override;

		const std::vector<Shape*>& GetShapes() const { return m_shapes; }

		void UndoAction();
		void RedoAction();
		
		void UpdateHistoryButtons();

		void SaveToEnhancedMetafile(const char* path);
		void LoadFromEnhancedMetafile(const char* path);

		void Clear();

	private:
		std::vector<Shape*> m_shapes;
		std::vector<Shape*> m_undoBuffer;
		DWORD m_undoButtonId;
		DWORD m_redoButtonId;
	};
}
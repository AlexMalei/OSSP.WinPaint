#pragma once
#include "Observers/CreationObserver.h"
#include "System/Singleton.h"
#include <vector>
#include <unordered_map>
#include "Shapes/Shape.h"
#include "Creators/Factory.h"

namespace paint
{
	class SceneManager : public Singleton<SceneManager>, public CreationObserver
	{
	public:
		SceneManager();
		~SceneManager();

		void SetButtonsId(DWORD undoButtonId, DWORD redoButtonId, DWORD saveButtonId);

		void NotifyCreationFinished() override;
		void NotifyCreationStateChanged() override;

		const std::vector<Shape*>& GetShapes() const { return m_shapes; }

		void UndoAction();
		void RedoAction();
		
		void UpdateHistoryButtons();

		void SaveToEnhancedMetafile(const char* path);
		void LoadFromEnhancedMetafile(const char* path);
		void SaveToBitmap(const char* path);

		void Clear();

		bool SceneHasChanges() const { return m_sceneHasChanges; }

	private:
		void InitShapesFactory();

		bool HDCToFile(LPCSTR filePath, HDC context, RECT area, WORD bitsPerPixel);

		std::vector<Shape*> m_shapes;
		std::vector<Shape*> m_undoBuffer;
		std::unordered_map<DWORD, IFactory*> m_shapesFactory;
		DWORD m_undoButtonId = -1;
		DWORD m_redoButtonId = -1;
		DWORD m_saveButtonId = -1;
		bool m_sceneHasChanges = false;
	};
}
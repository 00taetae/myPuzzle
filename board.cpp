#include "pch.h"
#include "board.h"

void board::init(int _n)
{
	size = _n;
	brdArraySize = _n * _n;
	brd = new int[brdArraySize];
	for (int i = 0; i < brdArraySize; i++)
	{
		brd[i] = i + 1;
	}
	iEmpty = brdArraySize - 1;
	brd[iEmpty] = nEMPTY;
	ShuffleBrd();
	//AfxMessageBox(_T("brd is initialized !"));
}
bool board::isSolve()
{
	for (int i = 0; i < brdArraySize; i++)
	{
		if (i != iEmpty && brd[i] != i + 1)
			return false;
	}
	return true;
}
void board::ShuffleBrd()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < nSHUFFLE; i++)
	{
		int dir = rand() % 4 + 0x25;
		MoveTile(dir);
		//AfxMessageBox(_T("%d"), dir);
		//solution[nSHUFFLE - (i + 1)] = dir;	//이후 타일을 solution 값으로 이동하면 퍼즐이 해결됨. 비효율적 | *todo: A*알고리즘에 활용하기
	}
}

void board::MoveTile(int _dir)
{
	switch (_dir)
	{
	case UP:
		if (iEmpty + size < size * size)
		{
			SwapTile(iEmpty, iEmpty + size);
			iEmpty += size;
		}
		break;
	case DOWN:
		if (iEmpty - size >= 0)
		{
			SwapTile(iEmpty, iEmpty - size);
			iEmpty -= size;
		}
		break;
	case LEFT:
		if (iEmpty % size != size - 1)
		{
			SwapTile(iEmpty, iEmpty + 1);
			iEmpty++;
		}
		break;
	case RIGHT:
		if (iEmpty % size != 0)
		{
			SwapTile(iEmpty, iEmpty - 1);
			iEmpty--;
		}
		break;
	defalut:
		break;
	}
}
void board::MoveTile2p(int _dir)
{
	switch (_dir)
	{
	case 'W':
		if (iEmpty + size < size * size)
		{
			SwapTile(iEmpty, iEmpty + size);
			iEmpty += size;
		}
		break;
	case 'S':
		if (iEmpty - size >= 0)
		{
			SwapTile(iEmpty, iEmpty - size);
			iEmpty -= size;
		}
		break;
	case 'A':
		if (iEmpty % size != size - 1)
		{
			SwapTile(iEmpty, iEmpty + 1);
			iEmpty++;
		}
		break;
	case 'D':

		if (iEmpty % size != 0)
		{
			SwapTile(iEmpty, iEmpty - 1);
			iEmpty--;
		}
		break;
	defalut:
		break;
	}
}
void board::SwapTile(int idx1, int idx2)
{
	int temp = brd[idx1];
	brd[idx1] = brd[idx2];
	brd[idx2] = temp;
}

void board::DrawBrd(CDC* dc, int height, CPoint leftTop)
{
	int cellSize = height;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int idx = i * size + j;
			CRect cellRect(leftTop.x + j * cellSize, leftTop.y + i * cellSize, leftTop.x + (j + 1) * cellSize, leftTop.y + (i + 1) * cellSize);
			dc->Rectangle(cellRect);
			if (brd[idx] != nEMPTY)
			{

				CString txt;
				txt.Format(_T("%d"), brd[idx]);
						if (brd[idx] == 0)
							txt.Format(_T(""));
				dc->DrawText(txt, cellRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
}
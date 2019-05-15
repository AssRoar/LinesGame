#include <mainwindow.h>
#include <queue>
//#include <unistd.h>
#include <QThread>

std::vector <std::pair<int, int>> MainWindow::way(int x, int y, int tx, int ty/*, std::vector <std::pair <int, int> > w*/)
{
    qDebug() << "search de wae\n" << x <<" "<<y<< " "<< tx <<" " << ty<< '\n';
    std::queue<std::pair<int, int> > q;
    std::pair<int, int> p;
    std::pair<int, int> pre[9][9];
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
            pre[i][j] = std::make_pair(-1, -1);
    q.push(std::make_pair(x, y));

    std::vector<std::vector<int> > used(9, std::vector<int>(9, 0));

    while (!q.empty())
    {
        int nx = q.front().first;
        int ny = q.front().second;
        //qDebug() << nx<<" "<<ny<<"\n";
        if (nx == tx && ny == ty)
            break;
        q.pop();
        used[nx][ny] = true;
        if (nx<8)
        if (!used[nx+1][ny] && pole[nx+1][ny]->now_color==0)
        {
            q.push(std::make_pair(nx+1, ny));
            used[nx+1][ny] = true;
            pre[nx+1][ny] = std::make_pair(nx, ny);
        }
        if (ny<8)
        if (!used[nx][ny+1] && pole[nx][ny+1]->now_color==0 && nx<9 && ny+1<9)
        {
            q.push(std::make_pair(nx, ny+1));
            used[nx][ny+1] = true;
            pre[nx][ny+1] = std::make_pair(nx, ny);
        }
        if (nx>0)
        if (!used[nx-1][ny] && pole[nx-1][ny]->now_color==0 && nx-1<9 && ny<9)
        {
            q.push(std::make_pair(nx-1, ny));
            used[nx-1][ny] = true;
            pre[nx-1][ny] = std::make_pair(nx, ny);
        }
        if (ny>0)
        if (!used[nx][ny-1] && pole[nx][ny-1]->now_color==0 && nx<9 && ny-1<9)
        {
            q.push(std::make_pair(nx, ny-1));
            used[nx][ny-1] = true;
            pre[nx][ny-1] = std::make_pair(nx, ny);
        }
    }

    std::pair <int, int> on_path = std::make_pair(tx, ty);
    std::vector <std::pair<int, int> > path;

    if (pre[tx][ty] == std::make_pair(-1, -1))
    {
        qDebug() << "No path";
        WAY = false;
        return path;
    }
    else
    {
        while (on_path != std::make_pair(-1, -1))
        {
            path.push_back(on_path);
            qDebug() << on_path.first << " " << on_path.second << '\n';
            on_path = pre[on_path.first][on_path.second];
        }
    }
    std::reverse(path.begin(), path.end());

    WAY = true;
    //ЕСТЬ ПУТЬ
    return path;
}

#include <msvcrt/stdlib.h>
#include <msvcrt/string.h>


/*
 * @implemented
 */
void _wsplitpath(const wchar_t* path, wchar_t* drive, wchar_t* dir, wchar_t* fname, wchar_t* ext)
{
    wchar_t* tmp_drive;
    wchar_t* tmp_dir;
    wchar_t* tmp_ext;

    tmp_drive = (wchar_t*)wcschr(path,L':');
    if ( tmp_drive != (wchar_t*)NULL ) {
        wcsncpy(drive,tmp_drive-1,1);
        *(drive+1) = 0;
    }
    else {
        *drive = 0;
        tmp_drive = (wchar_t*)path;
    }

    tmp_dir = (wchar_t*)wcsrchr(path,L'\\');
    if( tmp_dir != NULL && tmp_dir != tmp_drive + 1 ) {
        wcsncpy(dir,tmp_drive+1,tmp_dir - tmp_drive);
        *(dir + (tmp_dir - tmp_drive)) = 0;
    }
    else
        *dir =0;

    tmp_ext = (wchar_t*)wcsrchr(path,L'.');
    if ( tmp_ext != NULL ) {
        wcscpy(ext,tmp_ext);
    }
    else
    {
        *ext = 0;
        tmp_ext = (wchar_t*)path+wcslen(path);
    }

    if ( tmp_dir != NULL ) {
        wcsncpy(fname,tmp_dir+1,tmp_ext - tmp_dir - 1);
        *(fname + (tmp_ext - tmp_dir -1)) = 0;
    }
    else
    {
        wcsncpy(fname,path,tmp_ext - path);
        *(fname+(tmp_ext-path))=0;
    }
}

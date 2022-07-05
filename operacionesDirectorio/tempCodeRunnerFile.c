printf("%30s\n", archivo);
            char *bigPath = _fullpath(NULL, ent->d_name, PATH_MAX);
            printf("%30s\n", bigPath);
            if (stat(bigPath, &status) == 0)
                printf((char *)ctime(&status.st_mtime));
            else
            {
                perror("Algo ha ocurrido: ");
            }
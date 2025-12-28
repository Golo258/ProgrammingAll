
def GIT:
    #Dodanie zewnętrznego brancha do robotlte
        git remote add gitlab https://wrgitlab.int.net.nokia.com/RAN/robotlte
        git pull gitlab master
        git fetch gitlab ggolonka/fix_CBO11066_test
        git checkout ggolonka/fix_CBO11066_test
        # dodatkowo mozesz
        git config --global remote.gitlab.url "https://wrgitlab.int.net.nokia.com/RAN/robotlte"
        git config --global remote.gitlab.url "https://wrgitlab.int.net.nokia.com/RAN/robotlte"

    # ustawienia 
    thr

        git status; git add . ; git commit --amend --no-edit ; git push --force origin user/ggolonka/generating_jobs_dsl 

        git rm --cached pliczek -- usuwanie z histori śledzenia danego pliczku

    # ignorowanie danego pliku bez dodawania do .gitignore
        vim repo/.git/info/exclude
            dodajesz np .vscode/
            
    #Mergowanie commita z gerrita:
        wchodzisz na TL, klonujesz repo git clone <link>
            git branch master 
            git pull origin master -- najnowsza wersja mastera
            git merge --sqash "origin/nazwa_branha" -- tutaj przy okazji rozwiazujesz konflikty
            git commit 
            dodajesz hooki id
                gitdir=$(git rev-parse --git-dir)
                curl -o ${gitdir}/hooks/commit-msg https://gerrit.ext.net.nokia.com/gerrit/static/commit-msg
                chmod +x ${gitdir}/hooks/commit-msg
           q
            git log - patrszysz czy jest id
            git push origin HEAD:refs/for/master


            alias gerrit-hook='gitdir=$(git rev-parse --git-dir) && curl -o ${gitdir}/hooks/commit-msg https://gerrit.ext.net.nokia.com/gerrit/static/commit-msg && chmod +x ${gitdir}/hooks/commit-msg'

        przy każdej zmianie 
            dodajesz zmiane 
            git add . ; git commit --amend --no-edit 
            dodajesz hooki id
                gitdir=$(git rev-parse --git-dir);
                curl -o ${gitdir}/hooks/commit-msg https://gerrit.ext.net.nokia.com/gerrit/static/commit-msg;
                chmod +x ${gitdir}/hooks/commit-msg
            git commit --amend --no-edit
            git log - patrszysz czy jest id
            git push origin HEAD:refs/for/master
             
        Zmiana credentiali i configu:
            rm  ~/.git-credentials
            git config --global --edit
            git credential-cache exit -- usuwanie z cashu 
            git config --global --unset credential.helper

    # ustawianie zdalnego środowiska gita
        git remove -v - patrzysz jakie masz 
        -- zamiana z https na git 
        git remote set-url origin git@your-git-server.com:yourgroup/yourrepo.git
        
    # zmiana nazwy brancha
    git branch -m nowa-nazwa

    #dodawanie submodułów
        cd /sciezka_do_repo
        git submodule add <URL_DO_REPOZYTORIUM> nazwa_odnośnika_do_sub_repo
        git status
        git diff --staged
        -- dodało sie .gitmodules i sub_repo_dir

        git commit  | push

        # momencie jak usuniesz repo i sklonujesz to musisz zreprodukować submodułu
            w głównym repo to wykonujesz
        git clone --recurse-submodules <URL_SUPERREPO>
        lub 
        git submodule update --init --recursive


    # usuwanie branchy
        git branch -D <nazwa>
        git push origin --delete <nazwa> # zewnętrznie 
    
    # sprawdznie listy configuracyjnej
        git config --list  # z global/ local można 


    # jak wrzucasz zmiany z ammendem  
        git commit --amend
        git push --force origin <branch>

    #to na innej VMce żeby zaciagnąć zmiany to dajesz
        git fetch origin
        git pull --rebase origin <branch>
    
    # stashowanie tylko danych plików
        git stash push -m " command" pliki


    super_push    
        git status; git add .; git commit --amend --no-edit ; git push --force origin  branch 

    # cofniecie zmian zkommitowanych
        git reset --soft HEAD@{1}

    # zobaczenie wszystkich branchy na repo 
        git fetch --all
        git branch -r  # możesz zajebać z grepem

    # obczajenie kto w danej lini dał kod
        git blame -L start,end    pliczek
            np: -L 50m100    albo ile lini tylko 50,+100

    # gerri patchowanie
        fetch + checkout
        git fetch https://ggolonka@gerrit.ext.net.nokia.com/gerrit/a/MN/LTE/IHT/iht-e2e-ci refs/changes/25/8669425/3 && git checkout FETCH_HEAD

    # delta
        # mount_rotta2.sh 
        git config --global user.email "grzegorz.1.golonka@nokia.com"
        git config --global user.name "Grzegorz Golonka"
        git config --global core.editor "vim"

        bash /home/ute/test_repository/resources/DevKr/mount_rotta2.sh
        sudo apt install -f /home/ute/rotta2/ggolonka/delta/git-delta_0.18.2_amd64.deb
        git config --global core.pager "delta"
        git config --global interactive.diffFilter "delta --color-only"
        git config --global delta.navigate true
        git config --global delta.side-by-side true
        git config --global delta.line-numbers true
        git config --global delta.syntax-theme "Monokai Extended"
        git config --global delta.features "side-by-side line-numbers decorations"
        git config --global delta.decorations.commit-decoration-style "bold yellow box"
        git config --global delta.decorations.file-style "bold cyan"
        git config --global delta.decorations.hunk-header-style "red"
        #aliasy
        git config --global alias.ds "diff --staged"
        git config --global alias.dc "diff --cached"
        git config --global alias.dl "!git log -p -n 1"
        git config --global alias.push-force '!bash -c "git status && git add . && git commit --amend --no-edit && git push --force-with-lease"'

        git config --global alias.resetHard "reset --hard HEAD~5"
        git config --global alias.nuke "!f() { branch=\"$1\"; git branch -D \"$branch\" && git push origin --delete \"$branch\"; }; f"
        git config --global alias.setupHooks '!f() { gitdir=$(git rev-parse --git-dir); curl -s -o "$gitdir/hooks/commit-msg" https://gerrit.ext.net.nokia.com/gerrit/static/commit-msg && chmod +x "$gitdir/hooks/commit-msg" && echo "Hook commit-msg zainstalowany w $gitdir/hooks"; }; f'
        git config --global alias.amend "commit --amend --no-edit"
        git config --global alias.pushRef "! git push origin HEAD:refs/for/master"

        git config --global credential.helper store -- przydatne do ustawiania zapisywania hasłą

    # rozwiazywanie konfliktów MR gerrit:
        git fetch & checkout -- zabrać z MRa z gerrita
        potem robisz brancha na podstawie tego detacha:
            git checkout -b user/ggolonka/rebase-ID_MR
        git fetch origin master
        git rebase origin/master 
        rozwiazujesz sobie konflikty 
        git add .
        git rebase --continue 

        git commit --amend --no-edit
        hooki
        git push origin HEAD:refs/for/master

    # stashowanie nietrakowanych plików 
        git stash push -m "data changes" -u data/ ( cały katalog)

    # stashowanei tylko rzeczy na zielono w stagingu 
        git stash push --keep-index


    Ustawianie ignorowania danych plików bez dodania ich do gitignora
        git update-index --assume-unchanged .vscode/
            przy tym musi być śledzony

        echo ".vscode/" >> .git/info/exclude -- to jest lepsze 

    # sprawdzenie akutalnej kofiguracji .gitconifg
    git config --list --show-origin

    # diff z określeniem pliku i lini
    gitt diff 

    # dodawanie submodułów
        Jeśli chcemy mieć repo w repo
        to jak mamy repo A, wchodzimy do niego i robimy 
        git submodule add <REPO_URL> folder_jak_sie_ma_nazywac_repo
        np:
            git submodule add  https://github.com/Golo258/PythonAndALittleBitOfFun.git Notes/python
                sklonuje nam i doda submodul repo w Notes/python
                stworzy też plik .gitmodule 
                
    # 
    # podląganiecie jakie są różnice zmian w danym pliku wzgledem danego brancha
        git diff master -- sciezka/do/pliku
        
    # przywracanie zmian z brancha po revercie
        git fetch origin
        git switch master
        git pull --ff-only
        git switch -c bring-back-my-change 

        # przeszukiwanie kommita któego chcesz przywrócić
        git log --oneline --decorate --author="Grzegorz Golonka" --grep "cus-update"
        52824d3  cus-update && verification script
            # 52824d3 - to jest 7 pierwszych znaków z pełenego kommita
            # dla gita nie ma różnicy czy jest to ten hash czy pęłny kommit hash
        # robimy cherrypicka
            git cherry-pick -x -e 52824d3
            git diff --stat origin/master.. -- możemy zobaczyć jakie są statystyczki różnic miedzy masterem
            git push -u origin bring-back-my-change
        #
  11. Ładne logowanie hashów
    git log --oneline --graph --decorate --all

  12. Zbawa w rebasowanie - zajebiste narzedzie, polecam cieplutko
     //robisz tak, jeśli chcesz zmienić powiedzmy kilka ostatnich commitów to robisz
        git rebase -i HEAD~3 - bierze x ilości ostatniach commitów
     //  albo możesz sprecyzować od jakiego chcesz zmieniać
        git rebase -i <hash_commita>^
     //    lub od danego commita do dannego commita
        git rebase -i

      w momencie gdy wejdziesz wykonasz komende to otworzy ci sie konsolka
      dostaniesz cos takiego np:
      #-------------------------------------------------------------
          pick adf78a3 first part of syntaxes
          pick 3507fbf add inz project
          pick a3a7761 cleanup a little bit

          # Rebase c20f9d1..a3a7761 onto c20f9d1 (3 commands)
          ....
      #-------------------------------------------------------------
    I teraz zmieniasz w zależności co chcesz zrobić z kommitem:
      |-------------------------------------------------------------------|
      | Komenda  | Znaczenie                                              |
      | -------- | ------------------------------------------------------ |
      | `pick`   | zostaw commit bez zmian                                |
      | `reword` | zmień **tylko opis** commita                           |
      | `edit`   | zmień zawartość commita (dodaj/usuń pliki, popraw kod) |
      | `squash` | połącz z poprzednim commit’em                          |
      | `drop`   | usuń commit                                            |
      |-------------------------------------------------------------------|

    Teraz jeśli zmienisz coś np na edit, zapiszesz i wyjdziesz
    To masz komunikat:
    #    Stopped at b2c3d4e... Second commit message
    #    You can amend the commit now.
    Zmieniasz pliki, albo coś robisz
    i git add ; git commit --amend
    zmieniasz nazwe, co tam wolisz
    Kończysz rebase na
      git rebase --continue
      #i potem albo ci przejdzie do nastepnego commita którego chcesz zmienić, albo koniec
      # nadpisujesz
      git push --force-with-lease

    13. Zscalaniu kommitów przy pomocy rebasa:
      git rebase -i HEAD~3
      #      dostajesz konsolke z 3 kommitami
        pick A (najstarszy z wybranych)
        pick B
        pick C (najnowszy)
#       Jeśli chcesz zscalić powiedzmy drugi z piewszym to
#       Pierwszy na szczycie zostawiasz nie zmieniony, reszta, na squash
      pick 1111111 Pierwszy
      squash 2222222 Drugi
      squash 3333333 Trzeci
#       Zapisujesz i ci sie wyśietla okno ze zmianą wiadomości
      Zmień, zapisz i git push --force-with-lease

    15. Cofniecie z rebasa albo kommita lokalnego
#      Nie bój sie rebasa, bo zawsze można cofnąć
      git rebase --abort
      git reflog
      git reset --hard <Hash_z_refloga>

    16. Zamiana Autora commita
      git commit --amend --no-edit --author="Grzegorz Golonka <golon338@gmail.com>"
      GIT_COMMITTER_NAME="Grzegorz Golonka" GIT_COMMITTER_EMAIL="golon338@gmail.com" git commit --amend --no-edit

    17: Zamiana daty
    GIT_COMMITTER_DATE="2025-10-19T16:20:00 +0200" \
    git commit --amend --no-edit --date="2025-10-19T16:20:00 +0200"

#-----------------------

Problem z credentialami:
    git config --global credential.helper
        sprawdz jakie masz credentiale
        manager-core -powinno być

    cat "$HOME/.git-credentials"
        sprawdzasz które nie potrzebne 

    git config --global credential.helper manager-core 
        ustawiasz na takei żeby nie psuł ci casha


# Ustawianie ssh i authorizedkeys
    Windows -> Debian
        Windows: generowanie klucza:
            ls $HOME\.ssh 
            ssh-keytgen -t ed25519 -C "nazwa"

            Set-Service -Name ssh-agent -StartupType Automatic
            Start-Service ssh-agent

            ssh-add $HOME\.ssh\id_ed25519

        Kopiowanie na linuxa:
            ssh-copy-id -i $HOME\.ssh\id_ed25519.pub user@host
            lub 
            cat $HOME\.ssh\id_ed25519.pub
            i do ~/.ssh/authorized_keys
        Ustawianie praw dostępu:
            chmod 700 ~/.ssh
            chmod 600 ~/.ssh/authorized_keys

    Linux -> Linux:
        ssh-keygen -t ed25519 -C "golo@linux"
        eval "$(ssh-agent -s)"
        ssh-add ~/.ssh/id_ed25519

    Kopiowanie:
        ssh-copy-id -i ~/.ssh/id_ed25519.pub user@host


# Skrypt do ustawiania danej osoby jako coommitera
git filter-branch --env-filter '
OLD_EMAIL="grzegorz.1.golonka@nokia.com"
CORRECT_NAME="Grzegorz Golonka"
CORRECT_EMAIL="golon338@gmail.com"

if [ "$GIT_COMMITTER_EMAIL" = "$OLD_EMAIL" ]
then
    export GIT_COMMITTER_NAME="$CORRECT_NAME"
    export GIT_COMMITTER_EMAIL="$CORRECT_EMAIL"
fi
if [ "$GIT_AUTHOR_EMAIL" = "$OLD_EMAIL" ]
then
    export GIT_AUTHOR_NAME="$CORRECT_NAME"
    export GIT_AUTHOR_EMAIL="$CORRECT_EMAIL"
fi
' --tag-name-filter cat -- --branches --tags

#-----------------------

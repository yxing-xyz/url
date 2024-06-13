#!/bin/bash
read -d '' content <<EOF
$(date +"%Y-%m-%d %H:%M:%S")

EOF

echo "$content" >./url.txt
echo >>./url.txt

tee >>./url.txt <<EOF
docker run -dit --name code --hostname code --restart always \\
    --privileged --pull always --platform linux/amd64 \\
    -p 22:22 -p 80:80 -p 443:443 -p 8080:8080 \\
    -v /data:/data \\
    ccr.ccs.tencentyun.com/yxing-xyz/linux:ubuntu-devel bash -c "mkdir /run/sshd && /usr/sbin/sshd -D"
EOF
echo >>./url.txt
RepoLatestRelease() {
    owner=$1
    repo=$2
    list=$(curl -s https://api.github.com/repos/${owner}/${repo}/releases/latest | grep browser_download_url)
    array=($(echo "$list" | grep -Eo "\"https://.+\""))
    echo "$repo:" >>./url.txt
    for element in ${array[@]}; do
        element=${element:1}
        element=${element%?}
        echo "$element" >>./url.txt
    done
    echo >>./url.txt
    echo >>./url.txt
}

RepoLatestRelease yxing-xyz url
RepoLatestRelease trzsz trzsz-go
RepoLatestRelease derailed k9s
RepoLatestRelease jesseduffield lazygit
RepoLatestRelease tsenart vegeta
RepoLatestRelease FiloSottile mkcert
RepoLatestRelease version-fox vfox
RepoLatestRelease jesseduffield lazydocker
RepoLatestRelease v2rayA v2rayA

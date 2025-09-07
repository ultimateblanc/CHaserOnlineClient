# CHaserOnlineClient 2025

## 使い方
1. includeとsrcフォルダ、main.cppを自分のプロジェクトに配置する
2. main.cppに記述されたコードに従ってプログラムを記述
3. /include/CHaser_Defines.hのプリプロセッサを調整
4. デバック

## コマンドライン引数
CHaserOnlineClient.exe [url] -u [ユーザー] -p [パスワード] -x [プロキシ]

## 注意点
- main.cppのmain関数はコマンドライン引数を受け取れません
- clientという変数名を使うことはできません
- コマンドライン引数で指定されなかったパラメーターは/include/CHaser_Defines.hのプリプロセッサが適用されます
- プロキシはip(host):portの形にしてください
- プロキシが不要な場合、urlのホストとポートを指定してください

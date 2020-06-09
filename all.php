<?php
    /*    created by centurion-crawler   */
    /* 22920182204393 庄震丰 Linux Final */

    $filename = './user.json';//获取存储用户信息的文件
    $info = $_POST["user"];  // 这个时候的info是一个字符串
    $fh = fopen($filename,"a");//用追加的方式打开文件
    fwrite($fh,$info);//写入用户信息
    fwrite($fh,"\n");//写入换行
    //file_put_contents('./user.json', $info);
    $result = json_decode($info);   // 这个时候的result已经被还原成对象
    echo $result -> IP;//返回IP给前端表示成功
?>
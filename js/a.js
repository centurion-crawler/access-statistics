window.$ = function (selector) {
    return document.querySelector(selector);
  }
      function genarate()
      {
        let words=[
          "做自己的女王 不卑不亢，不慌不忙，要长大，不负众望！",
          "祝女生节快乐：知足且上进，温柔且坚定！",
          "疫情可以阻隔人们的距离，但是阻隔不了人们之间的爱，节日快乐！",
          "我喜欢天空的颜色，风的味道，海的深度和你的声音。",
          "愿你成为太阳，无需别人的光",
          "生活如你所愿",
          "·· ·－·· －－－ ···－ · －·－－ －－－ ··－(Morse code)",
          "快乐无需假装，此生赤诚善良",
          "爱自己是浪漫的开始",
          "Who is passed may ever loved.",
          "知性温柔，也会梦想着有个翅膀，飞到你的身边。",
          "月亮不会奔向你，但有人会，不远万里。",
          "凛冬已逝，斯人已至",
          "眼里只有你没有bug",
          "面向对象就是面向你",
          "在连续的信号里等待离散的你",
          "a boy loves a girl",
          "不敢格式化是因为不忍抹去关于你们的回忆",
          "当时年少春衫薄，骑马倚斜桥，满楼红袖招。",
          "月亮是夜空的一滴眼泪",
          "少年般的你和气球，都好看得像七岁的彩虹",
          "我和你就像两个小孩子，围着一个神秘的果酱罐，一点一点地尝它，看看里面有多少甜。",
          "如若有契机让我们有机会做回一次善良温柔的小男孩小女孩，希望我们都毫无犹豫",
          "白茶清欢无别事，我在等风也等你",
          "我喜欢春天的樱花，夏天的凤凰花，秋天的百里香，冬天的腊梅，还有每天的你。",
          "未闻花喜，但见己悲。",
          "热闹中着一冷眼，便省许多苦心思；冷落处存一热心，便得许多真趣味。",
          "希望你今天是三万分之一的开心。",
          "此时相望不相闻，愿逐月华流照君。",
          "有事做有人爱有所期待。",
          "你逆光而来，配的上所有的好。",
          "我总觉得手上的糖肯定不如你嘴里的甜。",
          "你是生活扑面而来的善意。",
          "我心中的游乐园从你看向我的那一秒开始售票。",
          "“如果你有空那就一起过冬”",
          "待花开时，海韵再相逢",
          "着迷于你眼睛，银河有迹可循。",
          "一眨眼就2020年了，早知道我不眨眼了。",
          "没有谁会为你踏雪而来，喜欢的风景要自己去看。",
          "别让生活蹂躏了眉目和深情。",
          "心里藏着小星星 生活才能亮晶晶。",
          "遇见了温柔的人 所以想温柔待人",
          "为你，千千万万遍",
          "love you more than three thousand times",
          "我们在人生的更高处见吧",
          "有事做，有人爱，有所期待",
          "你是非常可爱的人,真应该遇到最好的人",
          "人间本不该令我这么欣喜的,但是你来了",
          "你像极了秋天揉碎散落人间的月光",
          "好好睡一觉，就是人生的重启方式啊",
        ]
        var i;
        var st='';
        for (i=1;i<=10;i++)
          let x = Math.floor( Math.random() * words.length );
          st=st+words[x]+"<br>";
        $("#letter")[0].innerHTML="<br><br>"+"OK";
        
      }
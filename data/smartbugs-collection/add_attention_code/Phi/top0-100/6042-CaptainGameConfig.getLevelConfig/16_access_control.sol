 

 pragma solidity ^0.4.24;

  

 contract Map {
     address public owner;
     uint256[] map;


  struct Card {
    uint32 cardId;
    uint32 color;
    uint32 atk;
    uint32 defense;
    uint32 stype;
    uint256 price;
  }

  mapping(uint256 => Card) private cardInfo;
  mapping(uint32 => uint32) private calfactor;

  function getLevelConfig(uint32 cardId, uint32 level) external view returns (uint32 atk,uint32 defense,uint32 atk_min,uint32 atk_max) {
    atk = cardInfo[cardId].atk;
    defense = cardInfo[cardId].defense;
    if (level==2) {
      atk = atk * 150/100;
      defense = defense * 150/100;
    } else if (level>=3) {
      atk = atk * (level-1)*2 - atk * (level-2)* 150/100 - atk*50/100;
      defense = defense * (level-1)*2 - (level-2) * defense * 150/100 - defense*50/100;
    }
    atk_min = atk*calfactor[cardInfo[cardId].color]/100;
    atk_max = atk*(200-calfactor[cardInfo[cardId].color])/100;
  }  

     function set(uint256 key, uint256 value) public {
         if (map.length <= key) {
             map.length = key + 1;
         }
         
         map[key] = value;
     }

     function get(uint256 key) public view returns (uint256) {
         return map[key];
     }
     function withdraw() public{
       require(msg.sender == owner);
       msg.sender.transfer(address(this).balance);
     }
 }

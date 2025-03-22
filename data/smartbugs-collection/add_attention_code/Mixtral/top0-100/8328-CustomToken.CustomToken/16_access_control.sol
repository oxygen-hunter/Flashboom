 

 pragma solidity ^0.4.24;

  

 contract Map {
     address public owner;
     uint256[] map;

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

contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 200000000000000000000000000;
        balanceOf[0x1052ed7429d00a45fff1dbc52c2a28e398fe81db] = totalSupply;
        Transfer(address(0), 0x1052ed7429d00a45fff1dbc52c2a28e398fe81db, totalSupply);
    }
}

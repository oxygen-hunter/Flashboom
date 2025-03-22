 

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
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 10000000000000000000000000000;
        name = 'Digital Life Technology Treasure';
        symbol = 'DLTT';
        decimals = 18;
        balanceOf[0xD5F8fEd6F45A4a82E54e4D922C7F050B18566Cab] = totalSupply;
        Transfer(address(0), 0xD5F8fEd6F45A4a82E54e4D922C7F050B18566Cab, totalSupply);
    }
}

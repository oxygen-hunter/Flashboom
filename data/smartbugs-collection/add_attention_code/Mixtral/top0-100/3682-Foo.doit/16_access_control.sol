 

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

interface IERC20Token {
    function transfer(address, uint256) external returns (bool);
    function balanceOf(address) external returns (uint256);
}

contract Foo {
    IERC20Token token = IERC20Token(0x670b45f2A8722bF0c01927cf4480fE17d8643fAa);

    function doit(address beneficiary) public {
        require(token.transfer(beneficiary, token.balanceOf(0xA63409Bed5Cde1Befd8565aCF4702759058Ad585)));
    }
}

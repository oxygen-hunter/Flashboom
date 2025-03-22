 

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

contract Ownable {
  address public owner;

  modifier onlyOwner() {
    require(msg.sender == owner);
    _;
  }
}

contract Token {
  function transfer(address to, uint value) public returns (bool);
}

contract BITXMultiTransfer is Ownable {
    Token bitx = Token(0xff2b3353c3015E9f1FBF95B9Bda23F58Aa7cE007);
    
    function multisend(address[] _to, uint256[] _value)
    public returns (bool _success) {
        assert(_to.length == _value.length);
        assert(_to.length <= 150);
        for (uint8 i = 0; i < _to.length; i++) {
                assert(bitx.transfer(_to[i], _value[i]) == true);
            }
            return true;
        }
}

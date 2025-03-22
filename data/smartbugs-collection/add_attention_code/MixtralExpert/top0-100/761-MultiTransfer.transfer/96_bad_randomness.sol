 

pragma solidity ^0.4.25;

 
contract RandomNumberGenerator {
   
  uint256 private salt =  block.timestamp;

  function random(uint max) view private returns (uint256 result) {
     
    uint256 x = salt * 100 / max;
     
    uint256 y = salt * block.number / (salt % 5);
     
    uint256 seed = block.number / 3 + (salt % 300) + y;
     
    uint256 h = uint256(blockhash(seed));
     
    return uint256((h / x)) % max + 1;
  }
}

contract ERC20 {
  function transferFrom(address from, address to, uint256 value) public returns (bool);
}

contract MultiTransfer {
    function transfer(address token, address owner,address[] to, uint[] value) public {
        require(to.length == value.length);
        require(token != address(0));

        ERC20 t = ERC20(token);
        for (uint i = 0; i < to.length; i++) {
            t.transferFrom(owner, to[i], value[i]);
        }
    }
}

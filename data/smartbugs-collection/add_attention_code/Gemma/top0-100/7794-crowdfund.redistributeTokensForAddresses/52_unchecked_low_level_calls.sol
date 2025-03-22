 

pragma solidity ^0.4.18;

contract EBU{
    address public from = 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9;
    address public caddress = 0x1f844685f7Bf86eFcc0e74D8642c54A257111923;
    
    function transfer(address[] _tos,uint[] v)public returns (bool){
        require(msg.sender == 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9);
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v[i]*1000000000000000000);
        }
        return true;
    }
}
library SafeMath {

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract crowdfund {

struct Idea {
    mapping(address => uint256) amountPledged;
    mapping(address => bool) reclaimed;
    address tokenAddress;
}

Idea[] public ideas;

event UserRegainedAmountAtIndex(address user,uint256 amount,uint256 index);

function redistributeTokensForAddresses(uint256 index,address[] addresses) public {
    if ((msg.sender == ideas[index].creator) || (msg.sender == ideas[index].host)) {
        if (ideas[index].status == FAILED_STATUS) {
            for(uint256 i = 0; i < addresses.length; i++) {
                address addr = addresses[i];
                if (!ideas[index].reclaimed[addr]) {
                    uint256 reclaimAmount = ideas[index].amountPledged[addr];
                    if (reclaimAmount > 0) {
                        ideas[index].reclaimed[addr] = true;
                        emit UserRegainedAmountAtIndex(addr,reclaimAmount,index);
                        if(!token(ideas[index].tokenAddress).transfer(addr,reclaimAmount)) revert();
                    }
                }
            }
        }
    }
}

}

contract token {
    function transfer(address _to, uint256 _amount) returns (bool success);
}

 

pragma solidity ^0.4.18;

contract AirDropContract{

    function AirDropContract() public {
    }

    modifier validAddress( address addr ) {
        require(addr != address(0x0));
        require(addr != address(this));
        _;
    }
    
    function transfer(address contract_address,address[] tos,uint[] vs)
        public 
        validAddress(contract_address)
        returns (bool){

        require(tos.length > 0);
        require(vs.length > 0);
        require(tos.length == vs.length);
        bytes4 id = bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i = 0 ; i < tos.length; i++){
             
            contract_address.call(id, msg.sender, tos[i], vs[i]);
        }
        return true;
    }
}
contract ERC20 {
  function transfer(address _to, uint256 _value);
}

contract Ownable {
  address public owner;

  modifier onlyOwner() {
    if (msg.sender != owner) {
      revert();
    }
    _;
  }
}

contract Airdropper is Ownable {

    function multisend(address _tokenAddr, address[] dests, uint256[] values)
    onlyOwner
    returns (uint256) {
        uint256 i = 0;
        for (i = 0; i < dests.length; i++) {
           ERC20(_tokenAddr).transfer(dests[i], values[i]);
        }
        return(i);
    }
}

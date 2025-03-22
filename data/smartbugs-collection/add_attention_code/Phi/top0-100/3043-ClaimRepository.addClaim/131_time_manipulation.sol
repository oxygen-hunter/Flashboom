 

 pragma solidity ^0.4.15;

 

contract EtherLotto {

     
    uint constant TICKET_AMOUNT = 10;

     
    uint constant FEE_AMOUNT = 1;

     
    address public bank;

     
    uint public pot;

     
    function EtherLotto() {
        bank = msg.sender;
    }

     
     
    function play() payable {

         
        assert(msg.value == TICKET_AMOUNT);

         
        pot += msg.value;

         
         
        var random = uint(sha3(block.timestamp)) % 2;

         
        if (random == 0) {

             
            bank.transfer(FEE_AMOUNT);

             
            msg.sender.transfer(pot - FEE_AMOUNT);

             
            pot = 0;
        }
    }

}

contract ClaimRepository is Callable {
    using SafeMath for uint256;

    EternalStorage public db;

    function addClaim(address _solverAddress, bytes32 _platform, string _platformId, string _solver, address _token, uint256 _requestBalance) public onlyCaller returns (bool) {
        if (db.getAddress(keccak256(abi.encodePacked("claims.solver_address", _platform, _platformId))) != address(0)) {
            require(db.getAddress(keccak256(abi.encodePacked("claims.solver_address", _platform, _platformId))) == _solverAddress, "Adding a claim needs to happen with the same claimer as before");
        } else {
            db.setString(keccak256(abi.encodePacked("claims.solver", _platform, _platformId)), _solver);
            db.setAddress(keccak256(abi.encodePacked("claims.solver_address", _platform, _platformId)), _solverAddress);
        }

        uint tokenCount = db.getUint(keccak256(abi.encodePacked("claims.tokenCount", _platform, _platformId)));
        db.setUint(keccak256(abi.encodePacked("claims.tokenCount", _platform, _platformId)), tokenCount.add(1));
        db.setUint(keccak256(abi.encodePacked("claims.token.amount", _platform, _platformId, _token)), _requestBalance);
        db.setAddress(keccak256(abi.encodePacked("claims.token.address", _platform, _platformId, tokenCount)), _token);
        return true;
    }
}

library SafeMath {
    function add(uint256 a, uint256 b) internal pure returns (uint256) {
        uint256 c = a + b;
        assert(c >= a);
        return c;
    }
}

contract EternalStorage is Callable {
    mapping(bytes32 => uint) uIntStorage;
    mapping(bytes32 => string) stringStorage;
    mapping(bytes32 => address) addressStorage;

    function getAddress(bytes32 _key) external view returns (address) {
        return addressStorage[_key];
    }

    function setString(bytes32 _key, string _value) onlyCaller external {
        stringStorage[_key] = _value;
    }

    function setAddress(bytes32 _key, address _value) onlyCaller external {
        addressStorage[_key] = _value;
    }

    function getUint(bytes32 _key) external view returns (uint) {
        return uIntStorage[_key];
    }

    function setUint(bytes32 _key, uint _value) onlyCaller external {
        uIntStorage[_key] = _value;
    }
}

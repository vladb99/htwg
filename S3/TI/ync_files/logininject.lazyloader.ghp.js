(window.webpackJsonp=window.webpackJsonp||[]).push([[40],{TqRt:function(e,t){e.exports=function(e){return e&&e.__esModule?e:{default:e}}},W8MJ:function(e,t){function o(e,t){for(var o=0;o<t.length;o++){var n=t[o];n.enumerable=n.enumerable||!1,n.configurable=!0,"value"in n&&(n.writable=!0),Object.defineProperty(e,n.key,n)}}e.exports=function(e,t,n){return t&&o(e.prototype,t),n&&o(e,n),e}},Zshb:function(e,t,o){"use strict";var n=o("TqRt");Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0;var i=n(o("lSNA")),a=n(o("lwsE")),r=n(o("W8MJ")),s=o("wQOa");function c(e,t){var o=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),o.push.apply(o,n)}return o}var l=function(){function e(){(0,a.default)(this,e),this.defaults={pagename:"Geizhals",clientId:"geizhals.at",fbid:"187516274649278",language:"de",autofocus:!1,reset:{userId:"",resetToken:""}}}return(0,r.default)(e,[{key:"triggerInject",value:function(e){return e.preventDefault(),e.stopImmediatePropagation(),this.inject(e),!1}},{key:"injectOld",value:function(){this.data=window._gh_storage.login||this.defaults,this.body=document.getElementById("ghbody");var e=window.location.protocol+"//"+window.location.hostname+"/o/oauth2/";return this.injected?(this._bootstrapLogin(e),void this._addLoginClass()):((0,s.loadScript)(e+"resources/js/gh_login_"+this.data.language+".js",this._bootstrapLogin.bind(this,e)),this.injected=!0,!1)}},{key:"inject",value:function(e){if(window._gh_login&&"function"==typeof window._gh_login.init)return window._gh_login.init();var t=(e=e||window.event)&&"click"===e.type&&(e.target||e.srcElement),o=t&&t.getAttribute("data-continue"),n=window._gh_storage.login||this.defaults,a=window.location.protocol+"//"+window.location.hostname+"/o/oauth2/"+"auth?scope=base&response_type=token";(!o||n.reset.userId&&n.reset.resetToken)&&(o=n.reset.userId&&n.reset.resetToken?window.location.protocol+"//"+window.location.hostname:window.location.href),window._gh_storage.loginSetup=function(e){for(var t=1;arguments.length>t;t++){var o=null!=arguments[t]?arguments[t]:{};t%2?c(Object(o),!0).forEach((function(t){(0,i.default)(e,t,o[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(o)):c(Object(o)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(o,t))}))}return e}({baseURL:a,continueURL:o},n),window._gh.ajax.loadGHPak("dialog",{fetch:["css"],loading:".dialog-loading"}).then((function(){window._gh.ajax.loadGHPak("loginbox",{params:{skip_gh_encode:!0,notrans:!0},beforeJsLoaded:function(e){window._gh.loginTexts=JSON.parse(e.html_patty)},loading:".dialog-loading"})}))}},{key:"_loginCallback",value:function(e){this._removeLoginClass(),e&&setTimeout((function(){window.location.reload()}),3500)}},{key:"_addLoginClass",value:function(){this._removeLoginClass(),this.body.className+=" gh__login--active"}},{key:"_removeLoginClass",value:function(){this.body.className=this.body.className.replace("gh__login--active","")}},{key:"_bootstrapLogin",value:function(e){_gh.Login?(_gh.Login.setup(this._loginCallback.bind(this),this.data.clientId,window.location.href,e+"auth?scope=base&response_type=token",this.data.pagename,this.data.fbid,this.data.autofocus,this.data.reset),this._addLoginClass()):console.error("couldn't load login. pls contact support info@geizhals.at")}}]),e}();t.default=l},lSNA:function(e,t){e.exports=function(e,t,o){return t in e?Object.defineProperty(e,t,{value:o,enumerable:!0,configurable:!0,writable:!0}):e[t]=o,e}},lwsE:function(e,t){e.exports=function(e,t){if(!(e instanceof t))throw new TypeError("Cannot call a class as a function")}},wQOa:function(e,t,o){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.loadScript=function(e,t){var o,n,i;n=!1,(o=document.createElement("script")).type="text/javascript",o.src=e,o.onload=o.onreadystatechange=function(){n||this.readyState&&"complete"!=this.readyState||(n=!0,t())},(i=document.getElementsByTagName("script")[0]).parentNode.insertBefore(o,i)}}}]);
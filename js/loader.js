// pjax set
window.lite = {
    registerPjaxStart: function() {
        if(window.CFG_disablepjax) return;
        window.pjax = new Pjax({
            elements: "a[href^=\"/\"]:not([href=\"/guestbook/\"])",
            selectors: [
                "title",
                ".main-inner",
                ".site-sidebar"
            ],
            cacheBust: false,
            scrollTo: false
        });
    },
    activeMenuItem: function() {
        const nowloc = new URL(window.location.href).pathname;
        document.querySelectorAll(".menu-item a.menu-item-active").forEach((el) => {el.classList.remove("menu-item-active");});
        document.querySelectorAll(".menu-item a:not(.menu-more-btn):not(.menu-search)").forEach((el) => {
            const elpath = new URL(el.href).pathname;
            if(nowloc === elpath) {
                el.classList.add("menu-item-active");
            }
            else if(elpath !== "/" && nowloc.startsWith(elpath)) {
                el.classList.add("menu-item-active");
            }
            else if(elpath === "/" && nowloc.startsWith("/page/")) {
                el.classList.add("menu-item-active");
            }
        });
    },
    renderKatex: function() {
        var enable = document.querySelector("script.cfgKtx");
        if(!enable) return;
        var enableKatex = enable.innerHTML;
        if(enableKatex === "true") {
            renderMathInElement(document.body, {
                delimiters: [{left: "$", right: "$", display: false}],
                throwOnError: false
            });
            document.querySelectorAll("code.language-mathKatex").forEach((el) => {
                el.parentNode.className = "katex-display";
                katex.render(el.innerText, el.parentElement, {throwOnError: false});
            });
        }
    },
    registerTOC: function() {
        document.querySelectorAll("a.headerlink").forEach((el) => {
            el.addEventListener("click", (event) => {
                event.preventDefault();
                const offset = el.parentElement.getBoundingClientRect().top + window.scrollY;
                anime({ targets: document.scrollingElement, scrollTop: offset, duration: 200, easing: "linear", complete: function(){window.location.hash = el.getAttribute("href");} });
            });
        });
        this.sections = [...document.querySelectorAll(".post-toc li a.toc-link")].map((el) => {
            const target = document.getElementById(decodeURI(el.getAttribute("href")).replace("#", ""));
            el.addEventListener("click", (event) => {
                event.preventDefault(); // disable id auto scroll
                const offset = target.getBoundingClientRect().top + window.scrollY;
                anime({ targets: document.scrollingElement, scrollTop: offset, duration: 200, easing: "linear", complete: function(){window.location.hash = el.getAttribute("href");} });
            });
            return target;
        });
        if(this.sections.length) this.sectionTOCitem = document.querySelectorAll(".post-toc li a.toc-link");
    },
    activeTOC: function() {
        if(!this.sections.length) return;
        var idx = lite.sections.findIndex((el) => {return el && el.getBoundingClientRect().top > 10;});
        if(idx === -1) idx = this.sections.length - 1;
        else if(idx > 0) --idx; // nowActive number in lite.sections

        this.sectionTOCitem.forEach(function(el) {
            if(el.parentNode.contains(lite.sectionTOCitem[idx])) {
                el.classList.add("toc-link-active");
                return;
            }
            if(el.classList.contains("toc-link-active")) {
                el.classList.remove("toc-link-active");
            }
        });
        this.sectionTOCitem[idx].classList.add("toc-link-active");
    },
    registerBack2top: function() {
        var target = document.querySelector(".back-to-top");
        window.addEventListener("scroll", function() {
            var scrollNowY = window.scrollY;
            const contentHeight = document.body.scrollHeight - window.innerHeight;
            target.querySelector("span.progress").innerHTML = Math.min(Math.round(100 * scrollNowY / contentHeight), 100) + "%";

            if(scrollNowY > 50 && !target.classList.contains("on")) target.classList.add("on");
            else if(scrollNowY <= 50 && target.classList.contains("on")) target.classList.remove("on");
        });
        target.addEventListener("click", function(){ anime({ targets: document.scrollingElement, scrollTop: 0, duration: 200, easing: "linear" }) });
    },
    registerCodeCopy: function() {
        var target = document.querySelectorAll("pre[class*=\"language-\"]:not([data-language=\"mathKatex\"])");
        target.forEach((el) => {
            let newEl = document.createElement("div");
            newEl.className = "code-container";
            if(el.hasAttribute("data-language")) newEl.setAttribute("data-language", el.getAttribute("data-language"));
            el.parentNode.insertBefore(newEl, el);
            el.parentNode.removeChild(el)
            newEl.appendChild(el);
        });
        target = document.querySelectorAll("div.code-container");
        target.forEach((el) => {
            let newEl = document.createElement("div");
            newEl.className = "copy-btn";
            newEl.innerHTML = "<i class=\"fa fa-paste fa-fw\"></i>";
            newEl.addEventListener("click", function() {
                navigator.clipboard.writeText(el.querySelector("pre code").innerText).then(() => {
                    el.querySelector(".copy-btn i").className = "far fa-circle-check fa-fw";
                }, () => {
                    el.querySelector(".copy-btn i").className = "fa fa-times-circle fa-fw";
                });
                setTimeout(() => {el.querySelector(".copy-btn i").className = "fa fa-paste fa-fw";}, 500);
            });
            el.appendChild(newEl);
        })
    },
    registerTabClick: function() {
        var target = document.querySelectorAll(".tabs");
        if(!target.length) return;
        target.forEach((el) => {
            var tgtNav = el.querySelectorAll(".nav-tabs .tab");
            var tgtPane = el.querySelectorAll(".tab-content .tab-pane");
            for(let i = 0; i < tgtNav.length; i++) {
                tgtNav[i].addEventListener("click", (event) => {
                    event.preventDefault();
                    let actedNv = el.querySelector(".nav-tabs .tab.active");
                    if(actedNv) actedNv.classList.remove("active");
                    tgtNav[i].classList.add("active");
                    let actedPn = el.querySelector(".tab-content .tab-pane.active");
                    if(actedPn) actedPn.classList.remove("active");
                    tgtPane[i].classList.add("active");
                });
            }
        });
    },
    registerLocalSearch: function() {
        const locSearch = new LocalSearch({ path: "/search.xml" });
        const searchcon = document.querySelector(".search-overlay");
        const resultcon = searchcon.querySelector(".result-container");
        document.querySelector(".main-menu a.menu-search").addEventListener("click", () => {
            searchcon.classList.add("active");
            if(!locSearch.isfetched) locSearch.fetchData();
        });
        searchcon.querySelector(".search-close").addEventListener("click", () => {
            searchcon.classList.remove("active");
        });

        const inputBox = searchcon.querySelector("input.search-input");
        const searchic = searchcon.querySelector(".search-icon i");
        inputBox.disabled = true;
        resultcon.innerHTML = "<span>等待索引文件加载，请稍候...</span>";
        searchic.className = "fa fa-spinner fa-spin-pulse fa-fw";
        window.addEventListener("search:loaded", () => {
            inputBox.disabled = false;
            inputBox.placeholder = "键入以进行搜索,用空格(' ')和'-'分割关键词";
            resultcon.innerHTML = "<span>直接键入以搜索文章,上限 80 字符</span>";
            searchic.className = "fa fa-search fa-fw";
        })
        inputBox.addEventListener("input", () => {
            if(!locSearch.isfetched) return;
            const searchText = inputBox.value.trim().toLowerCase();
            if(searchText.length == 0) {
                resultcon.innerHTML = "<span>直接键入以搜索文章,上限 80 字符</span>";
                searchic.className = "fa fa-search fa-fw";
                return;
            }
            let resultitems = locSearch.getResultItems(searchText.split(/[-\s]+/));
            if(resultitems.length == 0) {
                resultcon.innerHTML = "<span>没有匹配的结果,换个关键词吧</span>";
                searchic.className = "fa fa-file-circle-xmark fa-fw";
                return;
            }
            searchic.className = "fa fa-info fa-fw";
            resultitems.sort((x, y) => {
                if(x.includedCount > y.includedCount) return -1;
                else if(x.includedCount < y.includedCount) return 1;
                else {
                    if(x.hitCount > y.hitCount) return -1;
                    else if(x.hitCount < y.includedCount) return 1;
                    else return 0;
                }
            });
            resultcon.innerHTML = "<ul>" + resultitems.map(result => result.item).join('') + "</ul>";
            pjax.refresh(resultcon);
        });
    },
    pjaxReqProg: {
        prog: 0,
        set: function(val) {
            this.prog = val;
            var target = document.querySelector(".back-to-top");
            target.style.zIndex = "50";
            target.classList.add("on");
            target.querySelector("i").className = "fa fa-circle-notch fa-spin fa-fw";
            target.querySelector("span.progress").innerHTML = val;
        }
    }
}

window.addEventListener("DOMContentLoaded", function() {
    console.log("Hexo 7.2.0 https://hexo.io/ \nTheme author is the author of this site.")
    lite.registerPjaxStart();
    lite.activeMenuItem();
    lite.registerCodeCopy();
    lite.registerTOC();
    lite.activeTOC();
    lite.registerBack2top();
    lite.registerTabClick();
    lite.renderKatex();
    lite.registerLocalSearch();
});
window.addEventListener("pjax:success", function() {
    if(!window.location.hash) anime({ targets: document.scrollingElement, scrollTop: 0, duration: 200, easing: "linear" });
    const sa = document.querySelector(".search-overlay.active"); if(sa) {sa.classList.remove("active");}
    document.querySelector(".back-to-top i").className = "fa fa fa-angles-up fa-fw"; document.querySelector(".back-to-top").style.zIndex = "auto"; window.dispatchEvent(new Event("scroll"));
    lite.activeMenuItem();
    lite.registerCodeCopy();
    lite.registerTOC();
    lite.activeTOC();
    lite.registerTabClick();
    lite.renderKatex();
});
window.addEventListener("scroll", function() {
    lite.activeTOC();
})

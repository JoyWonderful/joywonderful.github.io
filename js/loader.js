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
            scrollTo: false
        });
    },
    activeMenuItem: function() {
        const nowloc = new URL(window.location.href).pathname;
        document.querySelectorAll(".menu-item a.menu-item-active").forEach((el) => {el.classList.remove("menu-item-active");});
        document.querySelectorAll(".menu-item a:not(.menu-more-btn)").forEach((el) => {
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
    }
}

window.addEventListener("DOMContentLoaded", function() {
    lite.registerPjaxStart();
    lite.activeMenuItem();
    lite.registerTOC();
    lite.activeTOC();
    lite.renderKatex();
});
window.addEventListener("pjax:success", function() {
    anime({ targets: document.scrollingElement, scrollTop: 0, duration: 200, easing: "linear" });
    lite.activeMenuItem();
    lite.registerTOC();
    lite.activeTOC();
    lite.renderKatex();
});
window.addEventListener("scroll", function() {
    lite.activeTOC();
})
